#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BIGRAM_HASH_SIZE 131071
#define DICT_HASH_SIZE 262147

typedef struct {
    char **arr;
    int size;
    int cap;
} StrArr;

typedef struct bigram_node {
    char *first;
    StrArr seconds;
    struct bigram_node *next;
} BigramNode;

typedef struct {
    char *pre;
    char *err;
} ErrItem;

typedef struct {
    ErrItem *arr;
    int size;
    int cap;
} ErrList;

typedef struct dict_node {
    char *word;
    struct dict_node *next;
} DictNode;

// 全局变量
static BigramNode *bigram_hash[BIGRAM_HASH_SIZE] = {0};
static DictNode *dict_hash[DICT_HASH_SIZE] = {0};

// 字符串拷贝
static char *my_strdup(const char *s) {
    size_t len = strlen(s);
    char *p = (char *)malloc(len + 1);
    if (!p) exit(1);
    memcpy(p, s, len + 1);
    return p;
}

// 字符串数组操作
static void arr_init(StrArr *sa) {
    sa->size = 0;
    sa->cap = 4;
    sa->arr = (char **)malloc(sizeof(char *) * sa->cap);
}
static void arr_push_unique(StrArr *sa, char *str) {
    for (int i = 0; i < sa->size; ++i)
        if (strcmp(sa->arr[i], str) == 0) return;
    if (sa->size == sa->cap) {
        sa->cap *= 2;
        sa->arr = (char **)realloc(sa->arr, sizeof(char *) * sa->cap);
    }
    sa->arr[sa->size++] = str;
}

// 哈希函数
static unsigned int hash_str(const char *s, unsigned int mod) {
    unsigned int h = 5381;
    unsigned char c;
    while ((c = (unsigned char)*s++))
        h = ((h << 5) + h) + c;
    return h % mod;
}

// bigram哈希表操作
static BigramNode *get_bigram(char *first) {
    unsigned int idx = hash_str(first, BIGRAM_HASH_SIZE);
    BigramNode *cur = bigram_hash[idx];
    while (cur) {
        if (cur->first == first || strcmp(cur->first, first) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}
static void insert_bigram(char *first, char *second) {
    unsigned int idx = hash_str(first, BIGRAM_HASH_SIZE);
    BigramNode *cur = bigram_hash[idx];
    while (cur) {
        if (cur->first == first || strcmp(cur->first, first) == 0) break;
        cur = cur->next;
    }
    if (!cur) {
        cur = (BigramNode *)malloc(sizeof(BigramNode));
        cur->first = first;
        arr_init(&cur->seconds);
        cur->next = bigram_hash[idx];
        bigram_hash[idx] = cur;
    }
    arr_push_unique(&cur->seconds, second);
}

// 错误列表
static void errlist_init(ErrList *el) {
    el->size = 0;
    el->cap = 8;
    el->arr = (ErrItem *)malloc(sizeof(ErrItem) * el->cap);
}
static int errlist_has(ErrList *el, char *pre, char *err) {
    for (int i = 0; i < el->size; ++i)
        if (strcmp(el->arr[i].pre, pre) == 0 && strcmp(el->arr[i].err, err) == 0)
            return 1;
    return 0;
}
static void errlist_add(ErrList *el, char *pre, char *err) {
    if (errlist_has(el, pre, err)) return;
    if (el->size == el->cap) {
        el->cap *= 2;
        el->arr = (ErrItem *)realloc(el->arr, sizeof(ErrItem) * el->cap);
    }
    el->arr[el->size].pre = pre;
    el->arr[el->size].err = err;
    el->size++;
}

// 字典哈希表
static unsigned int dict_hash_func(const char *s) {
    unsigned int h = 5381;
    unsigned char c;
    while ((c = (unsigned char)*s++))
        h = ((h << 5) + h) + c;
    return h % DICT_HASH_SIZE;
}
static void load_dict(const char *path) {
    FILE *fp = fopen(path, "r");
    if (!fp) exit(1);
    char buf[1024];
    while (fgets(buf, sizeof(buf), fp)) {
        size_t len = strlen(buf);
        while (len && (buf[len - 1] == '\n' || buf[len - 1] == '\r' || buf[len - 1] == ' ' || buf[len - 1] == '\t'))
            buf[--len] = '\0';
        for (size_t i = 0; i < len; ++i)
            buf[i] = (char)tolower((unsigned char)buf[i]);
        char *dup = my_strdup(buf);
        unsigned int idx = dict_hash_func(dup);
        DictNode *node = (DictNode *)malloc(sizeof(DictNode));
        node->word = dup;
        node->next = dict_hash[idx];
        dict_hash[idx] = node;
    }
    fclose(fp);
}
static char *dict_lookup(const char *word) {
    unsigned int idx = dict_hash_func(word);
    DictNode *node = dict_hash[idx];
    while (node) {
        if (strcmp(node->word, word) == 0) return node->word;
        node = node->next;
    }
    return NULL;
}

// 编辑距离函数声明
#define max2(a,b) ((a)>(b)?(a):(b))
int **Dp, MaxDP=3300;								//for dynamic programming
int min3(int a, int b, int c)
{
    int min = a < b ? a : b;
    return min < c ? min : c;
}
int error2(char *s)
{
    fprintf(stderr,"%s\n",s); 
    exit(-1); 
}
int initDP()
{		
    int i;
    Dp = (int **)malloc(MaxDP*sizeof(int *));
    for(i=0; i<MaxDP; i++)
    Dp[i] = (int *)malloc(MaxDP*sizeof(int));
	return 0;	
}
int editdistDP(char *str1, char *str2) 
{
    int i,j;
    int len1, len2;
    static int flag=0;
    (flag++) ? 1 : initDP(); 
    len1 = strlen(str1)+1; len2 = strlen(str2)+1;
    (max2(len1,len2)>=MaxDP) ? error2("DP memory error!") : len1;
    for (i=0; i<=len1; i++) {
        for (j=0; j<=len2; j++) {
            if (i==0)
                Dp[i][j] = j;
            else if (j==0)
                Dp[i][j] = i;
            else if (str1[i-1] == str2[j-1])
                Dp[i][j] = Dp[i-1][j-1];
            else
                Dp[i][j] = 1 + min3(Dp[i][j-1], Dp[i-1][j], Dp[i-1][j-1]);
        }
    }
    return Dp[len1][len2];
}
// 解析输入文件
static int is_alpha(char c) {
    return ((unsigned)(c | 32) - 'a') < 26;
}
static void process_file(const char *path, ErrList *el) {
    FILE *fp = fopen(path, "rb");
    if (!fp) exit(1);
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    rewind(fp);
    if (fsize <= 0) { fclose(fp); return; }
    char *buf = (char *)malloc(fsize + 1);
    size_t readSz = fread(buf, 1, fsize, fp);
    buf[readSz] = '\0';
    fclose(fp);

    char *prev = NULL;
    int prev_ok = 0, prev_valid = 0;
    char *wstart = NULL;
    unsigned int h = 5381;

    for (char *p = buf; ; ++p) {
        char c = *p;
        if (is_alpha(c)) {
            char lower = (char)(c | 32);
            *p = lower;
            if (!wstart) {
                wstart = p;
                h = 5381;
            }
            h = ((h << 5) + h) + (unsigned char)lower;
        } else {
            if (wstart) {
                *p = '\0';
                char *dictPtr = dict_lookup(wstart);
                int is_ok = dictPtr != NULL;
                char *curPtr = is_ok ? dictPtr : my_strdup(wstart);

                if (prev_valid && prev_ok) {
                    if (is_ok)
                        insert_bigram(prev, curPtr);
                    else
                        errlist_add(el, prev, curPtr);
                }
                prev = curPtr;
                prev_ok = is_ok;
                prev_valid = 1;
                wstart = NULL;
            }
            if (c == '\0') break;
            if (c == ' ' || c == '\t') {
                // 保持bigram链
            } else {
                prev_valid = 0;
            }
        }
    }
    free(buf);
}

// 字符串比较
static int cmp_str(const void *a, const void *b) {
    return strcmp(*(char * const *)a, *(char * const *)b);
}

// 生成建议
static void gen_suggest(ErrList *el) {
    for (int i = 0; i < el->size; ++i) {
        char *pre = el->arr[i].pre;
        char *err = el->arr[i].err;
        BigramNode *entry = get_bigram(pre);
        printf("%s: %s -> ", pre, err);
        if (!entry || entry->seconds.size == 0) {
            printf("No suggestion\n");
            continue;
        }
        int minDist = -1;
        StrArr cands;
        arr_init(&cands);
        for (int j = 0; j < entry->seconds.size; ++j) {
            char *sec = entry->seconds.arr[j];
            int dist = editdistDP(err, sec);
            if (minDist == -1 || dist < minDist) {
                minDist = dist;
                cands.size = 0;
                arr_push_unique(&cands, sec);
            } else if (dist == minDist) {
                arr_push_unique(&cands, sec);
            }
        }
        if (cands.size == 0) {
            printf("No suggestion\n");
        } else {
            qsort(cands.arr, cands.size, sizeof(char *), cmp_str);
            for (int k = 0; k < cands.size; ++k) {
                printf("%s", cands.arr[k]);
                if (k != cands.size - 1) printf(",");
            }
            printf("\n");
        }
        free(cands.arr);
    }
}

int main() {
    load_dict("dict.txt");
    ErrList el;
    errlist_init(&el);
    process_file("in.txt", &el);
    gen_suggest(&el);
    return 0;
}
void statCount()
{
   for
}
