#include <stdio.h>
#include "sorter.h"


/**
 *  Insertion sort
 */
void insertion_sort (void** array, int size, CompareFunction compare, int ord_mode) {
    if (array != NULL && size > 1) {
        for (int i = 1; i < size; i++) {
            int j = i;
            while (j > 0 && compare(array[j-1], array[j]) * ord_mode > 0) {
                swap_elements(&array[j-1], &array[j]);
                j--;
            }
        }
    }
}


/**
 * Returns index of element used in quick_sort as pivot
 */

int partition (void** array, int from, int to, CompareFunction compare, int ord_mode) {
    int pivot = from;
    int i = from;
    int j = to;

    while (i < j) {
        while (i < to && compare(array[i], array[pivot]) * ord_mode <= 0)
            i++;
        while (j > from && compare(array[j],array[pivot]) * ord_mode > 0)
            j--;

        if (i <= j)
            swap_elements(&array[i], &array[j]);

    }
    swap_elements(&array[j], &array[pivot]);
    return j;
}

void quick_sort_int (void** array, int from, int to, CompareFunction compare, int ord_mode) {
    if (from < to) {
        int p = partition(array, from, to, compare, ord_mode);
        quick_sort_int(array, from, p-1, compare, ord_mode);
        quick_sort_int(array, p+1, to, compare, ord_mode);
    }
}

/**
 * Quick sort
 */
void quick_sort (void** array, int from, int to, CompareFunction compare, int ord_mode) {
    if (array != NULL) {
        quick_sort_int(array,from,to-1,compare, ord_mode);
    }
}

void swap_elements (void ** a , void ** b) {
    void* tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}