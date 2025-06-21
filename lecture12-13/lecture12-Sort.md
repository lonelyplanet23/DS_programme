# lecture 12 排序

---

## 1. 排序基本概念

### 1.1 排序的定义

给定记录序列 {R1, R2, ..., Rn}，通过确定一个置换序列 σ(1), σ(2), ..., σ(n)，使得排序后满足：

```text
k_σ(1) ≤ k_σ(2) ≤ ... ≤ k_σ(n)（升序）
```

排序：将原始无序数据元素序列转换为按关键字有序的序列

### 1.2 分类

* **内排序**：数据量小，全部装入内存排序
* **外排序**：数据量大，需借助外存中转

按方式：

* **比较类排序**：插入、选择、冒泡、快速、堆、归并、希尔
* **非比较排序**：计数、桶、基数排序（分配式排序）

### 1.3 性能指标

| 指标    | 描述                             |
| ----- | ------------------------------ |
| 时间复杂度 | 元素间比较次数 + 移动次数                 |
| 空间复杂度 | 排序过程中使用的辅助空间                   |
| 稳定性   | 相同值元素排序后相对位置是否保持不变（是：稳定，否：不稳定） |

> **注意**
> 比较次数 ≠ 移动次数， 警惕移动但不比较（往往是退出条件：插入、堆）

---

## 2. 插入排序 InsertSort

### 核心思想

第i趟将未排序子序列($\{i,i+1,...,n\}$) 的第一个元素插入到有序子序列(($\{0,1,..,i-1\}$))的合适位置
($i \isin \{1,2,...,n-1\}$)
+ 也就是说第i趟 将使得 $\{0,1,..,i\}$ 有序

交换位置
```text
有序：[A0, A1, ..., Ai-1] + 无序：[Ai, Ai+1, ..., An-1]
```

### 代码实现

```c
void InsertSort(ElemType A[], int n) {

  for(int i = 1; i < n; i++) {
    ElemType temp = A[i];
    //比较交换
    int j = i-1;
    for(; j >= 0 && temp < A[j]; j--)
    {
        A[j+1] = A[j]; //后移，直到A[j] 小于等于 temp 
    }

    A[j] = temp;
  }
}
```

### 时间与空间复杂度

| 情况 | 比较次数     | 交换次数   | 时间复杂度  |
| -- | -------- | ------ | ------ |
| 最好(已排序) | n-1      | 0      | O(n)   |
| 最坏 （逆序）| n(n-1)/2 | n(n-1)/2 | O(n^2) |
| 平均 | ≈n^2/4   | ≈n^2/4 | O(n^2) | 
| 空间 | -        | -      | O(1)   |

* 受初始排列影响
* 稳定性：**稳定**
* 优化：使用**折半查找**减少比较次数（移动次数不变）

---

## 3. 选择排序 SelectSort

### 核心思想

第i趟从无序序列($\{i, i+1,...,n\}$)中选出最小元素，放到前面已排序序列($\{0,1,..,i\}$)的末尾
($i \isin \{0,1,2,...,n-2\}$ 共n-1趟)
### 代码实现

```c
void SelectSort(ElemType A[], int n) {
  for(int i=0; i<n-1; i++) {
    int minIndex = i;

    for(int j=i+1; j<n; j++)
      if(A[j] < A[minIndex]) minIndex = j;

    if(minIndex != i)
      Swap(A[i], A[minIndex]);
  }
}
```

### 特点

* **不受初始排列影响**，比较次数始终为 n(n-1)/2
* 每次交换最多1次，共n-1次

| 时间复杂度 | O(n^2)  |
| ----- | ------- |
| 空间复杂度 | O(1)    |
| 稳定性   | **不稳定** |

---

## 4. 冒泡排序 BubbleSort
### 核心思想

第 $i$ 趟通过相邻元素两两比较，将当前无序序列 $\{0, 1, ..., n-i\}$ 中的最大元素“冒泡”到末尾，加入已排序序列 $\{n-i+1, ..., n\}$。

或者说
每一趟通过 $ \{0, 1, ..., i\}$ 相邻元素两两比较交换，选出第 $i$ 个 **最大值**
($i \isin \{n-1, n-2, ... , 1\}$)

### 代码实现

```c
void BubbleSort(ElemType A[], int n) {
  for(int i = n-1; i > 0; i++) {
    bool flag = false;

    for(int j = 0; j < i; j++) {
      if(A[j] > A[j+1]) {
        Swap(A[j], A[j+1]);
        flag = true; 
    }
    if(!flag) break; //优化，如果没有交换操作，则说明已有序。
      }
  }
}
```

| 时间复杂度 | 最优O(n)，最坏/平均O(n^2) |
| ----- | ------------------ |
| 空间复杂度 | O(1)               |
| 稳定性   | **稳定**             |

适合：**初始序列基本有序时**

---

## 5. 快速排序 QuickSort

### 核心思想

**分治法**：选择一个分界元素pivot，把小于它的移到左边，大于它的移到右边，对左右递归排序

### 双向扫描实现
双向扫描：**即，将大的和小的交换**
```c
void QuickSort(ElemType A[], int left, int right) {
  if(left >= right) return; //递归出口

  int i = left, j = right;
  ElemType pivot = A[left]; //找基准

  while(i < j) {
    
    while(A[j] >= pivot && i < j) j--;
    while(A[i] <= pivot && i < j) i++;
    
    if(i < j) swap(&A[i], &A[j]);

  }
/* i>j, 此时 i 停留在第一个比分界数大的位置
j 停留在最后一个比分界数小的位置*/
  swap(&A[left], A[j]); // 将基准数挪过来

  QuickSort(A, left, i-1);
  QuickSort(A, i+1, right);
}
```
单向扫描
```c


void QuickSort(ElemType A[], int left, int right) {
    int k; //小于pivot的指针

    if(left >= right) return;

    swap(&A[left], &A[(left+right)/2]); //优化方案：选取中间的为基准
    ElemType pivot = A[left];

    k = left;
    for(int i = left; i <= right; i++)
    {
        if(A[i] < pivot)
        {
            swap(&A[i], &A[++k]);
        }
    }
    //此时k指向最后一个小于pivot的位置
    swap(&A[left], &A[k]);
    QuickSort(A, left, i-1);
    QuickSort(A, i+1, right);
  }
```

| 情况  | 时间复杂度    | 空间复杂度   |
| --- | -------- | ------- |
| 最优  | O(nlogn) | O(logn) |
| 最坏（初始有序时，划分不平衡，始终pivot一侧无元素）  | O(n^2)   | O(n)    |
| 平均  | O(nlogn) | O(logn) |
| 稳定性 | **不稳定**  |         |

---

## 6. 归并排序 MergeSort

### 核心思想

分成左右两个子序列，各自排序，再合并成一个有序序列（适合**链表或大规模数据**）

### 归并实现（递归）

```c
void Merge(ElemType A[], ElemType tmp[], int left, int mid, int right) {
  int i = left, j = mid+1, k = left;
  
  //二路归并核心，比较谁小谁放。
  while(i <= mid && j <= right) {
    if(A[i] <= A[j]) tmp[k++] = A[i++];
    else tmp[k++] = A[j++];
  }
  // 复制两个子序列剩余部分
  while(i <= mid) tmp[k++] = A[i++];
  while(j <= right) tmp[k++] = A[j++];
  
  //复制
  for(i=left; i<=right; i++) A[i] = tmp[i];
}

void MergeSort(ElemType A[], ElemType tmp[], int left, int right) {
  //核心递归实现
  if(left < right) {
    int mid = (left + right) / 2;
    
    MergeSort(A, tmp, left, mid);

    MergeSort(A, tmp, mid+1, right);

    Merge(A, tmp, left, mid, right);
  }
}

void mergeSort(keytype k[],int n){
    keytype *tmp;
    tmp = (keytype *)malloc(sizeof(keytype) * n);
    if(tmp != NULL) {
        mSort(k, tmp, 0, n-1);
        free(tmp);
    }
    else
        printf(“No space for tmp array!!!\n”);
 }

```
与原序列无关

| 时间复杂度 | O(nlogn) n是归并，logn是分割 |
| ----- | -------- |
| 空间复杂度 | O(n)     |
| 稳定性   | **稳定**   |

---

## 7. 堆排序 HeapSort

### 核心思想

用\*\*堆结构（大根堆）\*\*选出最大值，交换到数组末尾，然后调整堆结构，重复直到全部排序

### 代码核心

```c
//见堆的下滤
void AdjustDown(ElemType A[], int i, int n) {
  int j = 2*i + 1;
  ElemType temp = A[i];
  while(j < n) {
    if(j+1 < n && A[j] < A[j+1]) j++;
    if(temp >= A[j]) break;
    A[i] = A[j]; i = j; j = 2*i + 1;
  }
  A[i] = temp;
}

void HeapSort(ElemType A[], int n) {
  //建堆：从最后一个非叶子结点（n/2 - 1）向前逐个“下滤”
  for(int i = n/2-1; i >= 0; i--)
    AdjustDown(A, i, n);
  //堆排序主体：把最大值移到最后，并把剩下的 i 个元素重新整理为堆
  for(int i = n-1; i > 0; i--) {
    Swap(A[0], A[i]);
    AdjustDown(A, 0, i);
  }
}
```

| 时间复杂度 | O(nlogn) |
| ----- | -------- |
| 空间复杂度 | O(1)     |
| 稳定性   | **不稳定**  |

**例题：已知序列25,13,10,12,9是大顶堆，在序列尾部插入新元素18，将其再调整为大顶堆。调整过程中元素之间进行的比较次数是**

## 🔽 操作：插入一个新元素 18 到堆尾

插入后数组变为：

```
25, 13, 10, 12, 9, 18
```

新元素 `18` 在索引 5，对应树结构：

```
        25
       /  \
     13    10
    /  \    /
  12   9  18
```

我们现在需要对这个堆进行\*\*“上滤”（上浮）\*\*操作，让 `18` 在合适位置。

## ✅ 总共比较次数：

* 第一次比较 `18` vs `10` → 交换 → **1 次**
* 第二次比较 `18` vs `25` → 不交换 → **1 次**

**→ 一共进行了 2 次比较**


---

## 8. 希尔排序 ShellSort

### 核心思想

分组插入排序。先设定gap（间隔）（一般设为n/2），将所有间隔为gap的元素为一组排序，再不断缩小gap直到1。
>> gap = 4; [8, 9, 1, 3 | 2, 5, 4, 0]
>> 对每一组：[8,2] [9,5] [1,4] [3,0] 进行插入排序，即每组分别从2,5,4,0开始，向前插入（交换）
>> 变成 [2, 5, 1, 0 | 8, 9, 4, 3]
>> gap = 2 ...

### 代码示意

```c
void shellSort(int arr[], int n) {
    // 初始间隔从 n/2 开始，逐步缩小
    for (int gap = n / 2; gap > 0; gap /= 2) 
    {
        // 对每个 gap 分组做插入排序: 
        for (int i = gap; i < n; i++) 
        {
            int temp = arr[i];
            int j;
            // 类似插入排序，但跳跃式比较
            for(int j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap]; // 向下交换
            }
            arr[j] = temp;
        }
    }
}

```

| 时间复杂度 | 介于 O(n) 与 O(n^2)（取决于gap序列） |
| ----- | -------------------------- |
| 空间复杂度 | O(1)                       |
| 稳定性   | **不稳定**                    |

---

## 9. 非比较排序（略）

### 示例

* 计数排序 Counting Sort
* 桶排序 Bucket Sort
* 基数排序 Radix Sort

特点：利用数值特性，无需比较，时间复杂度近线性
限制：元素范围受限，适合整数且范围不大场景

---

## 排序算法性能对比表

| 排序方法   | 平均情况                      | 最好情况          | 最坏情况          | 辅助空间                  | 稳定性 |
| ------ | ------------------------- | ------------- | ------------- | --------------------- | --- |
| 冒泡排序   | $O(n^2)$                  | $O(n)$        | $O(n^2)$      | $O(1)$                | 稳定  |
| 简单选择排序 | $O(n^2)$                  | $O(n^2)$      | $O(n^2)$      | $O(1)$                | 不稳定 |
| 直接插入排序 | $O(n^2)$                  | $O(n)$        | $O(n^2)$      | $O(1)$                | 稳定  |
| 希尔排序   | $O(n \log n) \sim O(n^2)$ | $O(n^{1.3})$  | $O(n^2)$      | $O(1)$                | 不稳定 |
| 堆排序    | $O(n \log n)$             | $O(n \log n)$ | $O(n \log n)$ | $O(1)$                | 不稳定 |
| 归并排序   | $O(n \log n)$             | $O(n \log n)$ | $O(n \log n)$ | $O(n)$                | 稳定  |
| 快速排序   | $O(n \log n)$             | $O(n \log n)$ | $O(n^2)$      | $O(\log n) \sim O(n)$ | 不稳定 |


---

## 核心总结

1. 插入/冒泡稳定，适合小规模或基本有序数据
2. 快排最快，适合大部分情况；归并适合大数据且要求稳定
3. 选择/堆/希尔不稳定，但空间占用低
4. 排序在一趟结束后可选出一个元素放在其**最终位置**上：
    1.  可以确定：选择、冒泡、堆排（都是选出了第几个最大或者最小）、**快排**。
    2.  不可以确定：插入（局部有序）、归并（子区间合并）、希尔。
5. 综合选择：

```text
• 有序 → 插入排序
• 无序小数据 → 插入/选择/冒泡
• 大数据 → 快排 / 归并 / 堆排
• 稳定性要求 → 归并
```
