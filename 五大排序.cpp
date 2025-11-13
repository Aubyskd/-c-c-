#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>


//冒泡排序
void bubbleSort(std::vector<double>& arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        // 每次循环将最大的元素冒泡到末尾
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // 交换相邻元素
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

//选择排序
void selectionSort(std::vector<double>& arr) 
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        // 找到未排序部分中的最小元素
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // 将最小元素放到已排序部分的末尾
        std::swap(arr[i], arr[min_idx]);
    }
}

//插入排序
void insertionSort(std::vector<double>& arr) 
{
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        double key = arr[i];
        int j = i - 1;

        // 将比key大的元素向右移动
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

//归并排序
// 合并两个已排序的子数组
void merge(std::vector<double>& arr, int left, int mid, int right) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // 创建临时数组
    std::vector<double> L(n1), R(n2);

    // 复制数据到临时数组
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // 合并临时数组
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) 
    {
        if (L[i] <= R[j]) 
        {
            arr[k] = L[i];
            i++;
        }
        else 
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // 复制L[]的剩余元素
    while (i < n1) 
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // 复制R[]的剩余元素
    while (j < n2) 
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// 归并排序的递归实现
void mergeSort(std::vector<double>& arr, int left, int right) 
{
    if (left < right) 
    {
        // 找到中点
        int mid = left + (right - left) / 2;

        // 递归排序左右两半
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // 合并已排序的两半
        merge(arr, left, mid, right);
    }
}

//快速排序
// 快速排序的分区函数
int partition(std::vector<double>& arr, int low, int high) 
{
    double pivot = arr[high]; // 选择最后一个元素作为基准
    int i = low - 1; // 小于基准的元素的最后位置

    for (int j = low; j < high; j++) 
    {
        // 如果当前元素小于等于基准
        if (arr[j] <= pivot) 
        {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// 快速排序的递归实现
void quickSort(std::vector<double>& arr, int low, int high) 
{
    if (low < high) 
    {
        // 获取分区点
        int pi = partition(arr, low, high);

        // 递归排序分区点左右两侧的子数组
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


/*
## 五种排序算法的重点总结
### 1. 冒泡排序 (Bubble Sort)
- 基本思想 ：重复遍历数组，比较相邻元素并交换位置
- 时间复杂度 ：最坏O(n²)，平均O(n²)，最好O(n)（已排序情况）
- 空间复杂度 ：O(1)
- 稳定性 ：稳定
- 适用场景 ：数据量小，几乎已排序的数据
- 优点 ：实现简单，容易理解
- 缺点 ：效率低，数据量大时表现差
### 2. 选择排序 (Selection Sort)
- 基本思想 ：每次从未排序部分找出最小元素，放到已排序部分末尾
- 时间复杂度 ：最坏O(n²)，平均O(n²)，最好O(n²)
- 空间复杂度 ：O(1)
- 稳定性 ：不稳定
- 适用场景 ：数据量小，对稳定性没有要求
- 优点 ：交换次数少
- 缺点 ：时间复杂度固定，无法利用数据的有序性
### 3. 插入排序 (Insertion Sort)
- 基本思想 ：将未排序元素插入到已排序部分的适当位置
- 时间复杂度 ：最坏O(n²)，平均O(n²)，最好O(n)（已排序情况）
- 空间复杂度 ：O(1)
- 稳定性 ：稳定
- 适用场景 ：数据量小，几乎已排序的数据
- 优点 ：实现简单，对部分有序数据效率高
- 缺点 ：数据量大时效率低
### 4. 归并排序 (Merge Sort)
- 基本思想 ：分治法，将数组分成两半，递归排序后合并
- 时间复杂度 ：最坏O(n log n)，平均O(n log n)，最好O(n log n)
- 空间复杂度 ：O(n)
- 稳定性 ：稳定
- 适用场景 ：对稳定性有要求，数据量大，外部排序
- 优点 ：稳定，时间复杂度稳定，适合链表排序
- 缺点 ：需要额外空间，递归调用栈开销
### 5. 快速排序 (Quick Sort)
- 基本思想 ：选择基准元素，将数组分为小于和大于基准的两部分，递归排序
- 时间复杂度 ：最坏O(n²)（已排序情况），平均O(n log n)，最好O(n log n)
- 空间复杂度 ：O(log n)（递归调用栈）
- 稳定性 ：不稳定
- 适用场景 ：数据量大，对稳定性没有要求
- 优点 ：平均情况下最快，原地排序
- 缺点 ：最坏情况下效率低，不稳定
### 算法选择建议
1. 1.
   数据量小 ：插入排序通常是最佳选择
2. 2.
   数据几乎已排序 ：插入排序或冒泡排序
3. 3.
   数据量大且要求稳定 ：归并排序
4. 4.
   数据量大且内存受限 ：堆排序（虽未列出）
5. 5.
   一般情况下数据量大 ：快速排序（实际应用中最常用）
*/