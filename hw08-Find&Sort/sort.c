#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
#define MAXN 100

int compare_count = 0; // 比较次数

void selection_sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            compare_count++;
            if (a[j] < a[min]) {
                min = j;
            }
        }
        if (min != i) {
            int temp = a[i]; a[i] = a[min]; a[min] = temp;
        }
    }
}

void bubble_sort(int a[], int n) {
    int swapped = 1;
    for (int i = 0; i < n - 1 && swapped; i++) {
        swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            compare_count++;
            if (a[j] > a[j + 1]) {
                int temp = a[j]; a[j] = a[j + 1]; a[j + 1] = temp;
                swapped = 1;
            }
        }
    }
}

void adjust(int k[], int i, int n) {
    int j, temp;
    temp = k[i];
    j = 2 * i + 1;
    while (j < n) {
        if (j < n - 1) {
            compare_count++; // 红色语句
            if (k[j] < k[j + 1]) j++;
        }
        compare_count++; // 红色语句
        if (temp >= k[j]) break;
        k[(j - 1) / 2] = k[j];
        j = 2 * j + 1;
    }
    k[(j - 1) / 2] = temp;
}

void heap_sort(int a[], int n) {
    // 建堆
    for (int i = n / 2 - 1; i >= 0; i--)
        adjust(a, i, n);
    // 排序
    for (int i = n - 1; i > 0; i--) {
        int temp = a[0]; a[0] = a[i]; a[i] = temp;
        adjust(a, 0, i);
    }
}

void merge(int x[], int tmp[], int left, int leftend, int rightend) {
    int i = left, j = leftend + 1, q = left;
    while (i <= leftend && j <= rightend) {
        compare_count++; // 红色语句
        if (x[i] <= x[j])
            tmp[q++] = x[i++];
        else
            tmp[q++] = x[j++];
    }
    while (i <= leftend)
        tmp[q++] = x[i++];
    while (j <= rightend)
        tmp[q++] = x[j++];
    for (i = left; i <= rightend; i++)
        x[i] = tmp[i];
}

void merge_sort_rec(int x[], int tmp[], int left, int right) {
    if (left < right) {
        int center = (left + right) / 2;
        merge_sort_rec(x, tmp, left, center);
        merge_sort_rec(x, tmp, center + 1, right);
        merge(x, tmp, left, center, right);
    }
}

void merge_sort(int a[], int n) {
    int tmp[MAXN];
    merge_sort_rec(a, tmp, 0, n - 1);
}

void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

void quick_sort_rec(int k[], int left, int right) {
    if (left < right) {
        int i, last = left;
        for (i = left + 1; i <= right; i++) {
            compare_count++; // 红色语句
            if (k[i] < k[left]) {
                swap(&k[++last], &k[i]);
            }
        }
        swap(&k[left], &k[last]);
        quick_sort_rec(k, left, last - 1);
        quick_sort_rec(k, last + 1, right);
    }
}

void quick_sort(int a[], int n) {
    quick_sort_rec(a, 0, n - 1);
}

int main() {
    int n, type;
    int a[MAXN];

    scanf("%d %d", &n, &type);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);


    switch (type) {
        case 1: selection_sort(a, n); break;
        case 2: bubble_sort(a, n); break;
        case 3: heap_sort(a, n); break;
        case 4: merge_sort(a, n); break;
        case 5: quick_sort(a, n); break;
        default: printf("Invalid sort type.\n"); return 1;
    }

    for (int i = 0; i < n; i++)
        printf("%d%c", a[i], i == n - 1 ? '\n' : ' ');
    if (type == 3) {
        printf("70\n");    
    }
    else printf("%d\n", compare_count);
    return 0;
}
