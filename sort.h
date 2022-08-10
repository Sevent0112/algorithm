//
// Created by Sevent on 2022/8/9.
//

#ifndef ALGORITHM_SORT_H
#define ALGORITHM_SORT_H
#include<string.h>
#include <memory>

template<typename T>
void swap(T& a, T& b){
    int temp = a;
    a = b;
    b = temp;
}
template<typename T>
void BubbleSort(T* array, size_t size, bool order = true)
// order true 时从小到大，反之为从大到小
{
    if (array== nullptr || size < 2)
        return;
    for (int i = 0; i < size - 1; ++i)
        for(int j = i + 1; j < size;++j){
            if (order){
                if (array[i] > array[j])
                    swap(array[i], array[j]);
            }
            else{
                if (array[i] < array[j])
                    swap(array[i], array[j]);
            }
        }
}

template<typename T>
void SelectSort(T *array, size_t size, bool order = true)
{
    if(array == nullptr || size < 2)
        return;
    for (int i = 0; i < size - 1; ++i) {
        int targetIndex = i;
        for (int j = i + 1; j < size; ++j) {
            if (order)
                targetIndex = array[targetIndex] < array[j] ? targetIndex : j;
            else targetIndex = array[targetIndex] < array[j] ? j : targetIndex;
        }
        swap(array[i], array[targetIndex]);
    }
}

template<typename T>
void InsertSort(T* array, size_t size, bool order = true)
{
    if (array == nullptr || size < 2)
        return ;
    for (int i = 1; i < size; ++i) {
        if (order){
            for (int j = i - 1; j >=0 && array[j] > array[j+1] ; --j)
                swap(array[j], array[j+1]);
        }
        else{
            for (int j = i-1; j >=0 && array[j] < array[j+1] ; --j)
                swap(array[j], array[j+1]);
        }
    }
}

template<typename T>
void ShellSort(T* array, int len, bool order =  true) {
    if (array == nullptr || len < 2)
        return;
    for (int d = len >> 1; d > 0; d = d >> 1) {
        for (int i = d; i < len; i++) {
            if (order) {
                for (int j = i - d; j >= 0 && array[j] > array[j + 1]; j -= d)
                    swap(array[j], array[j + 1]);
            } else {
                for (int j = i - d; j >= 0 && array[j] < array[j + 1]; j -= d)
                    swap(array[j], array[j + 1]);
            }
        }
    }
}

template<typename T>
static void merge_sort_recursive(T* arr, T* reg, int start, int end, bool order) {
    if (start >= end)
        return;
    int mid =(start + end) >> 1;
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = end;
    merge_sort_recursive(arr, reg, start1, end1, order);
    merge_sort_recursive(arr, reg, start2, end2, order);
    int k = start;
    while (start1 <= end1 && start2 <= end2) {
        if (order)
            reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
        else
            reg[k++] = arr[start1] < arr[start2] ? arr[start2++] : arr[start1++];
    }
    while (start1 <= end1)
        reg[k++] = arr[start1++];
    while (start2 <= end2)
        reg[k++] = arr[start2++];
    for (k = start; k <= end; k++)
        arr[k] = reg[k];
}

// merge_sort
template<typename T>
void MergeSort(T* array, const int len, bool order = true) {
    if (array == nullptr || len < 2)
        return;
    T reg[len];
    merge_sort_recursive(array, reg, 0, len - 1, order);
}

template<typename T>
void quick_recursive(T* array, int begin, int end, bool order)
{
    if (begin > end)
        return;
    T pivot = array[begin];
    int l = begin;
    int r = end;
    while(l != r){
        while(array[r] >= pivot && l < r)
            r--;
        while(array[l] <= pivot && l < r)
            l++;
        if (l < r)
            swap(array[l], array[r]);
    }
    swap(array[begin], array[l]);
    quick_recursive(array, begin, l-1, order);
    quick_recursive(array, l+1, end, order);
}
template<typename T>
void QuickSort(T* array, int len, bool order = true)
{

    if (array == nullptr || len < 2)
        return;
    quick_recursive(array, 0, len-1, order);

}

template<typename T>
void keepHeap(T* array, int head, int len, bool order)
{
    if (head >= (len >> 1))
        return;
    int maxIndex = array[head<<1] > array[head<<1|1]? head<<1:head<<1|1;
    if (array[head] < array[maxIndex]) {
        swap(array[head], array[maxIndex]);
        keepHeap(array, maxIndex, len, order);
    }
}

template<typename T>
void HeapSort(T* array, int len, bool order = true)
{
    if (array == nullptr||len < 2)
        return;
    for (int noLeftIndex = (len>>1) - 1; noLeftIndex >=0 ; --noLeftIndex)
        keepHeap(array, noLeftIndex, len, order);
    swap(array[0], array[len - 1]);
    HeapSort(array, len - 1, order);
}

template<typename T>
void CountSort(T* array, int len, int order = true)
{
    T max = array[0];
    T min = array[0];
    for (int i = 0; i < len; ++i) {
        max = max > array[i]? max : array[i];
        min = min > array[i]? array[i] : min;
    }
    int  l = max - min + 1;
    T* counter = new int[max - min + 1]();
    for (int i = 0; i < len; ++i)
        counter[array[i] - min]++;
    int index = 0;
    for (int i = 0; i < l; ++i) {
        while(counter[i] > 0 && index < len) {
            array[index++] = i + min;
            counter[i]--;
        }
    }
    delete[] counter;
}

template<typename T>
int maxBits(T* array, int len)
{
    T max = array[0];
    for (int i = 0; i < len; ++i) {
        max = max > array[i]? max:array[i];
    }
    int bits = 0;
    while(max>0){
        bits++;
        max /= 10;
    }
    return bits;
}

template<typename T>
void bitSort(T* array, int len, int exp, bool order = true)
{
    int* tmp = new int[len]();
    int count[10] = {0};
    for (int i = 0; i < len; ++i)
        count[(array[i]/exp)%10]++;

    for (int i = 1; i < 10; ++i)
        count[i] += count[i - 1];

    for (int i = len - 1; i >= 0 ; --i) {
        tmp[count[(array[i]/exp)%10] - 1] = array[i];
        --count[(array[i]/exp)%10];
    }

    for (int i = 0; i < len; ++i) {
        array[i]  = tmp[i];
    }

}
template<typename T>
void RadixSort(T* array, int len, bool order = true)
{
    int bits  = maxBits(array, len);
    int exp = 1;
    for (int i = 0; i < bits; i++) {
        bitSort(array, len, exp, order);
        exp *= 10;
    }
}
#endif //ALGORITHM_SORT_H
