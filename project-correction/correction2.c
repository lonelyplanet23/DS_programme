// correction.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 提供跨平台安全的 strdup 实现
#ifndef _MSC_VER
#include <strings.h>
#endif

static char *my_strdup(const char *s) {
    size_t len = strlen(s);
    char *p = (char *)malloc(len + 1);
    if (!p) {
        fprintf(stderr, "Out of memory while duplicating string\n");
        exit(1);
    }
    memcpy(p, s, len + 1);
    return p;
}
#define strdup my_strdup

// Declaration of edit distance function implemented in editdistDP.c
int editdistDP(char *word1, char *word2);

/* ----------------------------- Data structures ----------------------------*/

typedef struct {
    char **data;
    int size;
    int capacity;
} StringArray;

static void sa_init(StringArray *sa) {
    sa->size = 0;
    sa->capacity = 4;
    sa->data = (char **)malloc(sizeof(char *) * sa->capacity);
}
static void sa_push_unique(StringArray *sa, char *str) {
    // Ensure uniqueness (linear scan sufficient for small volume)
    for (int i = 0; i < sa->size; ++i) {
        if (strcmp(sa->data[i], str) == 0) return;
    }
    if (sa->size == sa->capacity) {
        sa->capacity *= 2;
        sa->data = (char **)realloc(sa->data, sizeof(char *) * sa->capacity);
    }
    sa->data[sa->size++] = str;
}

// Bigram entry: first word -> set of second words

typedef struct BigramEntry {
    char *first;          // 指向词典中首词的指针，保证唯一
    StringArray seconds;  // second 单词集合（去重）
    struct BigramEntry *next; // 哈希冲突链
} BigramEntry;

// 基于哈希表的  first->seconds  索引，加快插入与查询
#define BIGRAM_HT_SIZE 131071  // 质数，减小冲突
static BigramEntry *bigramHT[BIGRAM_HT_SIZE] = {0};

static unsigned int hash_str(const char *s) {
    unsigned int h = 5381;
    unsigned char c;
    while ((c = (unsigned char)*s++)) {
        h = ((h << 5) + h) + c; // h*33 + c
    }
    return h % BIGRAM_HT_SIZE;
}

static BigramEntry *bm_get_entry(char *firstWord) {
    unsigned int idx = hash_str(firstWord);
    BigramEntry *cur = bigramHT[idx];
    while (cur) {
        if (cur->first == firstWord || strcmp(cur->first, firstWord) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}

static void bm_insert(char *firstWord, char *secondWord) {
    unsigned int idx = hash_str(firstWord);
    BigramEntry *entry = bigramHT[idx];
    while (entry) {
        if (entry->first == firstWord || strcmp(entry->first, firstWord) == 0) break;
        entry = entry->next;
    }
    if (!entry) {
        entry = (BigramEntry *)malloc(sizeof(BigramEntry));
        entry->first = firstWord;
        sa_init(&entry->seconds);
        entry->next = bigramHT[idx];
        bigramHT[idx] = entry;
    }
    sa_push_unique(&entry->seconds, secondWord);
}

// 由于改为全局哈希表，这些空实现用于保持后续代码接口一致，避免大幅修改
typedef struct { int dummy; } BigramMap;
static void bm_init(BigramMap *bm) { (void)bm; }
/*--------------------------------------------------------------------------*/

/* -------------------------- Error entry structure -------------------------*/

typedef struct {
    char *prevWord;  // correct word before error (dictionary pointer)
    char *errorWord; // dynamically allocated lowercase string
} ErrorItem;

typedef struct {
    ErrorItem *data;
    int size;
    int capacity;
} ErrorList;

static void el_init(ErrorList *el) {
    el->size = 0;
    el->capacity = 8;
    el->data = (ErrorItem *)malloc(sizeof(ErrorItem) * el->capacity);
}
static int el_contains(ErrorList *el, char *prevWord, char *errorWord) {
    for (int i = 0; i < el->size; ++i) {
        if (strcmp(el->data[i].prevWord, prevWord) == 0 && strcmp(el->data[i].errorWord, errorWord) == 0) {
            return 1;
        }
    }
    return 0;
}
static void el_add(ErrorList *el, char *prevWord, char *errorWord) {
    if (el_contains(el, prevWord, errorWord)) return;
    if (el->size == el->capacity) {
        el->capacity *= 2;
        el->data = (ErrorItem *)realloc(el->data, sizeof(ErrorItem) * el->capacity);
    }
    el->data[el->size].prevWord = prevWord;
    el->data[el->size].errorWord = errorWord;
    el->size++;
}

/* ----------------------------- Dictionary ---------------------------------*/

// -------------------------- Dictionary (hash, djb2) ------------------------

#define DICT_HT_SIZE 262147 // 2^18+3，质数
typedef struct DictNode {
    char *word;
    struct DictNode *next;
} DictNode;

static DictNode *dictHT[DICT_HT_SIZE] = {0};

static unsigned int dict_hash(const char *s) {
    unsigned int h = 5381;
    unsigned char c;
    while ((c = (unsigned char)*s++)) {
        h = ((h << 5) + h) + c;
    }
    return h % DICT_HT_SIZE;
}

static void load_dictionary(const char *path) {
    FILE *fp = fopen(path, "r");
    if (!fp) {
        fprintf(stderr, "Failed to open dict file: %s\n", path);
        exit(1);
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp)) {
        size_t len = strlen(buffer);
        while (len && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r' || buffer[len - 1] == ' ' || buffer[len - 1] == '\t')) {
            buffer[--len] = '\0';
        }
        for (size_t i = 0; i < len; ++i) buffer[i] = (char)tolower((unsigned char)buffer[i]);
        char *dup = strdup(buffer);
        unsigned int idx = dict_hash(dup);
        DictNode *node = (DictNode *)malloc(sizeof(DictNode));
        node->word = dup;
        node->next = dictHT[idx];
        dictHT[idx] = node;
    }
    fclose(fp);
}

static inline char *dict_lookup_hash(unsigned int preHash, const char *word) {
    unsigned int idx = preHash % DICT_HT_SIZE;
    DictNode *node = dictHT[idx];
    while (node) {
        if (strcmp(node->word, word) == 0) return node->word;
        node = node->next;
    }
    return NULL;
}

static char *dict_lookup(const char *word) {
    return dict_lookup_hash(dict_hash(word), word);
}

/* ---------------------- Utility: lowercase conversion ---------------------*/

// 工具函数已不再使用，若需要转换可直接在局部实现。

/* -------------------------------- Parsing ---------------------------------*/

static inline int is_letter(char c) {
    return ((unsigned)(c | 32) - 'a') < 26; // 只适用于ASCII字母
}

static void process_file(const char *path, BigramMap *bm, ErrorList *el) {
    FILE *fp = fopen(path, "rb");
    if (!fp) {
        fprintf(stderr, "Failed to open input file: %s\n", path);
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    rewind(fp);
    if (fsize <= 0) { fclose(fp); return; }
    char *buf = (char *)malloc(fsize + 1);
    size_t readSz = fread(buf, 1, fsize, fp);
    buf[readSz] = '\0';
    fclose(fp);

    char *prevWord = NULL;
    int prevIsCorrect = 0;
    int prevValid = 0;

    char *wordStart = NULL;
    unsigned int h = 5381; // running hash

    for (char *p = buf; ; ++p) {
        char c = *p;
        if (is_letter(c)) {
            char lower = (char)(c | 32);
            *p = lower; // inplace tolower
            if (!wordStart) {
                wordStart = p;
                h = 5381;
            }
            h = ((h << 5) + h) + (unsigned char)lower;
        } else {
            if (wordStart) {
                *p = '\0'; // terminate word
                char *dictPtr = dict_lookup_hash(h, wordStart);
                int isCorrect = dictPtr != NULL;
                char *currentWordPtr = isCorrect ? dictPtr : strdup(wordStart);

                if (prevValid && prevIsCorrect) {
                    if (isCorrect)
                        bm_insert(prevWord, currentWordPtr);
                    else
                        el_add(el, prevWord, currentWordPtr);
                }

                prevWord = currentWordPtr;
                prevIsCorrect = isCorrect;
                prevValid = 1;
                wordStart = NULL;
            }

            if (c == '\0') break;

            if (c == ' ' || c == '\t') {
                // keep bigram chain
            } else {
                prevValid = 0;
            }
        }
    }

    free(buf);
}

/* ----------------------------- Suggestions --------------------------------*/

static int cmpStr(const void *a, const void *b) {
    return strcmp(*(char * const *)a, *(char * const *)b);
}

static void generate_suggestions(BigramMap *bm, ErrorList *el) {
    for (int i = 0; i < el->size; ++i) {
        char *prevWord = el->data[i].prevWord;
        char *errorWord = el->data[i].errorWord;
        BigramEntry *entry = bm_get_entry(prevWord);
        printf("%s: %s -> ", prevWord, errorWord);
        if (!entry || entry->seconds.size == 0) {
            printf("No suggestion\n");
            continue;
        }
        int minDist = -1;
        StringArray candidates;
        sa_init(&candidates);
        for (int j = 0; j < entry->seconds.size; ++j) {
            char *second = entry->seconds.data[j];
            int dist = editdistDP(errorWord, second);
            if (minDist == -1 || dist < minDist) {
                // found better
                minDist = dist;
                candidates.size = 0; // reset
                sa_push_unique(&candidates, second);
            } else if (dist == minDist) {
                sa_push_unique(&candidates, second);
            }
        }
        if (candidates.size == 0) {
            printf("No suggestion\n");
        } else {
            // sort lexicographically
            qsort(candidates.data, candidates.size, sizeof(char *), cmpStr);
            for (int k = 0; k < candidates.size; ++k) {
                printf("%s", candidates.data[k]);
                if (k != candidates.size - 1) printf(",");
            }
            printf("\n");
        }
        // free candidates array (not strings)
        free(candidates.data);
    }
}

/* --------------------------------- Main -----------------------------------*/

int main() {
    load_dictionary("dict.txt");

    BigramMap bm; // 占位，接口一致
    bm_init(&bm);
    ErrorList el;
    el_init(&el);

    process_file("in.txt", &bm, &el);

    generate_suggestions(&bm, &el);

    return 0;
} 