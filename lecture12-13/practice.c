#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<wchar.h>
#include<locale.h>
// 快速排序核心函数：分治 + 递归
void quickSort(int arr[], int left, int right) {
    if (left >= right) return;  // 基础情况
    
    int pivot = arr[left];      // 选最左边为基准
    int i = left, j = right;    // 左右指针
    
    while (i < j) {
        // 从右往左找第一个小于pivot的
        while (i < j && arr[j] >= pivot) j--;
        // 从左往右找第一个大于pivot的
        while (i < j && arr[i] <= pivot) i++;
        if (i < j) {
            // 交换i和j的值
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    // 基准值归位（此时i==j）
    arr[left] = arr[i];
    arr[i] = pivot;

    // 对左右子区间递归排序
    quickSort(arr, left, i - 1);
    quickSort(arr, i + 1, right);
}

// 打印数组（辅助函数）
void printArray(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 主函数
int main() {
    int arr[] = {9, 4, 6, 2, 7, 1, 5, 8, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("原始数组:\n");
    printArray(arr, n);

    quickSort(arr, 0, n - 1);

    printf("排序后数组:\n");
    printArray(arr, n);

    return 0;
}
