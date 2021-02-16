#pragma once

typedef int (*CompareFunction)(void*, void*);

/**
 *  Sort input array using Insertion sort algorithm
 *  Parameters:
 *  - array: array to sort
 *  - size: size of array
 *  - compare: function that compare two objects
 *  - ord_mode: ordering mode (1: ascending, -1: descendant)
 */
void insertion_sort(void** array, int size, CompareFunction compare, int ord_mode);


/**
 *  Sort input array using Quicksort algorithm
 *  Parameters:
 *  - array: array to sort
 *  - size: size of array
 *  - compare: function that compare two objects
 *  - ord_mode: specify ordering mode (1: ascending, 2: descending)
 */
void quick_sort(void** array, int from, int to, CompareFunction compare, int ord_mode);

/**
 *  Swaps two elements 
 */ 
void swap_elements(void ** a , void ** b);