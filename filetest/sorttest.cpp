#include <stdio.h>
#include "./../thirdparty/ctest.h"
//#include "./../sorts/sorts.cpp"

extern void selectionSort(int data[], int lenD);
extern void bubbleSort(int data[], int len);
extern void insertionSort(int data[], int len);
extern void mergeSort(int data[], int lenD);
extern void quickSort(int *data, int const len);

CTEST(sort_tests, selection_sort_test)
{
    int data[] = {64, 25, 12, 22, 11};
    int expected[] = {11, 12, 22, 25, 64};
    int len = sizeof(data) / sizeof(data[0]);

    selectionSort(data, len);

    for (int i = 0; i < len; i++) {
        ASSERT_EQUAL(expected[i], data[i]);
    }
}

CTEST(sort_tests, bubble_sort_test)
{
    int data[] = {5, 1, 4, 2, 8};
    int expected[] = {1, 2, 4, 5, 8};
    int len = sizeof(data) / sizeof(data[0]);

    bubbleSort(data, len);

    for (int i = 0; i < len; i++) {
        ASSERT_EQUAL(expected[i], data[i]);
    }
}

CTEST(sort_tests, insertion_sort_test)
{
    int data[] = {12, 11, 13, 5, 6};
    int expected[] = {5, 6, 11, 12, 13};
    int len = sizeof(data) / sizeof(data[0]);

    insertionSort(data, len);

    for (int i = 0; i < len; i++) {
        ASSERT_EQUAL(expected[i], data[i]);
    }
}

CTEST(sort_tests, merge_sort_test)
{
    int data[] = {38, 27, 43, 3, 9, 82, 10};
    int expected[] = {3, 9, 10, 27, 38, 43, 82};
    int len = sizeof(data) / sizeof(data[0]);

    mergeSort(data, len);

    for (int i = 0; i < len; i++) {
        ASSERT_EQUAL(expected[i], data[i]);
    }
}

CTEST(sort_tests, quick_sort_test)
{
    int data[] = {10, 7, 8, 9, 1, 5};
    int expected[] = {1, 5, 7, 8, 9, 10};
    int len = sizeof(data) / sizeof(data[0]);

    quickSort(data, len);

    for (int i = 0; i < len; i++) {
        ASSERT_EQUAL(expected[i], data[i]);
    }
}