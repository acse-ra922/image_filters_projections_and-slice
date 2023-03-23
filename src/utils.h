//
// Created by Wang, Yuyang on 19/03/2023.
//

#pragma once
#include <vector>

template <typename T>
void quickSort(std::vector<T> &arr, int left, int right) {
    int i = left, j = right;
    T tmp;
    T pivot = arr[(left + right) / 2];

    /* partition */
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    /* recursion */
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}
