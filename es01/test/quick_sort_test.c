#include <stdlib.h>
#include "../../Resources/C/Unity/unity.h"
#include "sorter.h"

static int* int_new(int n) {
    int* result = (int*) malloc (sizeof(int));
    *result = n;

    return result;
}

static int **create_array(int *values, int size) {
    int **array = (int**) malloc(sizeof(int*) * size);
    for (int i = 0; i < size; i++) {
        array[i] = int_new(values[i]);
    }
    return array;
}

static int compare(int* obj1, int* obj2) {
    return *obj1 - *obj2;
}

static void quick_sort_null() {
    void** a = NULL;

    quick_sort(a, 0, 0, (CompareFunction) compare, 1);

    TEST_ASSERT_EQUAL(a, NULL);
}

static void quick_sort_single_element_array() {
    int** a;
    int v[] = {8};
    a = create_array(v, 1);

    quick_sort((void*) a, 0,1, (CompareFunction) compare, 1);

    TEST_ASSERT_EQUAL(8, *a[0]);
}

static void quick_sort_ordered_array() {
    int** a;
    int v[] = {3, 5, 6, 8, 11, 14, 16, 19};
    a = create_array(v, 8);

    quick_sort((void*) a, 0, 8, (CompareFunction) compare, 1);

    TEST_ASSERT_EQUAL(3, *a[0]);
    TEST_ASSERT_EQUAL(5, *a[1]);
    TEST_ASSERT_EQUAL(6, *a[2]);
    TEST_ASSERT_EQUAL(8, *a[3]);
    TEST_ASSERT_EQUAL(11, *a[4]);
    TEST_ASSERT_EQUAL(14, *a[5]);
    TEST_ASSERT_EQUAL(16, *a[6]);
    TEST_ASSERT_EQUAL(19, *a[7]);
}

static void quick_sort_inv_ordered_array() {
    int **a;
    int v[] = {19, 16, 14, 11, 8, 6, 5, 3};
    a = create_array(v, 8);

    quick_sort((void*) a, 0, 8, (CompareFunction) compare, 1);

    TEST_ASSERT_EQUAL(3, *a[0]);
    TEST_ASSERT_EQUAL(5, *a[1]);
    TEST_ASSERT_EQUAL(6, *a[2]);
    TEST_ASSERT_EQUAL(8, *a[3]);
    TEST_ASSERT_EQUAL(11, *a[4]);
    TEST_ASSERT_EQUAL(14, *a[5]);
    TEST_ASSERT_EQUAL(16, *a[6]);
    TEST_ASSERT_EQUAL(19, *a[7]);
}

static void quick_sort_unordered_array() {
    int **a;
    int v[] = {19, 8, 3, 6, 11, 14, 5, 16};
    a = create_array(v, 8);

    quick_sort((void*) a, 0, 8, (CompareFunction) compare, 1);

    TEST_ASSERT_EQUAL(3, *a[0]);
    TEST_ASSERT_EQUAL(5, *a[1]);
    TEST_ASSERT_EQUAL(6, *a[2]);
    TEST_ASSERT_EQUAL(8, *a[3]);
    TEST_ASSERT_EQUAL(11, *a[4]);
    TEST_ASSERT_EQUAL(14, *a[5]);
    TEST_ASSERT_EQUAL(16, *a[6]);
    TEST_ASSERT_EQUAL(19, *a[7]);
}

static void quick_sort_unordered_array_descending() {
    int **a;
    int v[] = {19, 8, 3, 6, 11, 14, 5, 16};
    a = create_array(v, 8);

    quick_sort((void*) a, 0, 8, (CompareFunction) compare, -1);

    TEST_ASSERT_EQUAL(19, *a[0]);
    TEST_ASSERT_EQUAL(16, *a[1]);
    TEST_ASSERT_EQUAL(14, *a[2]);
    TEST_ASSERT_EQUAL(11, *a[3]);
    TEST_ASSERT_EQUAL(8, *a[4]);
    TEST_ASSERT_EQUAL(6, *a[5]);
    TEST_ASSERT_EQUAL(5, *a[6]);
    TEST_ASSERT_EQUAL(3, *a[7]);
}

static void quick_sort_same_elements() {
    int **a;
    int v[] = {5,5,5,5,5};
    a = create_array(v, 5);

    quick_sort((void*) a, 0, 5, (CompareFunction) compare, 1);

    TEST_ASSERT_EQUAL(5, *a[0]);
    TEST_ASSERT_EQUAL(5, *a[1]);
    TEST_ASSERT_EQUAL(5, *a[2]);
    TEST_ASSERT_EQUAL(5, *a[3]);
    TEST_ASSERT_EQUAL(5, *a[4]);
}

static void quick_sort_duplicates() {
    int **a;
    int v[] = {19, 8, 3, 6, 14, 14, 5, 16};
    a = create_array(v, 8);

    quick_sort((void*) a, 0, 8, (CompareFunction) compare, 1);

    TEST_ASSERT_EQUAL(3, *a[0]);
    TEST_ASSERT_EQUAL(5, *a[1]);
    TEST_ASSERT_EQUAL(6, *a[2]);
    TEST_ASSERT_EQUAL(8, *a[3]);
    TEST_ASSERT_EQUAL(14, *a[4]);
    TEST_ASSERT_EQUAL(14, *a[5]);
    TEST_ASSERT_EQUAL(16, *a[6]);
    TEST_ASSERT_EQUAL(19, *a[7]);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(quick_sort_null);
    RUN_TEST(quick_sort_single_element_array);
    RUN_TEST(quick_sort_ordered_array);
    RUN_TEST(quick_sort_inv_ordered_array);
    RUN_TEST(quick_sort_unordered_array);
    RUN_TEST(quick_sort_unordered_array_descending);
    RUN_TEST(quick_sort_same_elements);
    RUN_TEST(quick_sort_duplicates);
    UNITY_END();
}