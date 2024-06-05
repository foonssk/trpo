#include <cstring>
#include <iostream>
#include <sorts/sorts.h>

// Function to print an array
void
printArray (const int arr[], int size)
{
  for (int i = 0; i < size; i++)
    {
      std::cout << arr[i] << " ";
    }
  std::cout << std::endl;
}

// Function to check if an array is sorted
bool
isSorted (const int arr[], int size)
{
  for (int i = 1; i < size; i++)
    {
      if (arr[i - 1] > arr[i])
        {
          return false;
        }
    }
  return true;
}

// Main function to test the sorting algorithms
int
main ()
{
  int data1[] = { 64, 25, 12, 22, 11 };
  int data2[] = { 64, 25, 12, 22, 11 };
  int data3[] = { 64, 25, 12, 22, 11 };
  int data4[] = { 64, 25, 12, 22, 11 };
  int data5[] = { 64, 25, 12, 22, 11 };
  int data6[] = { 64, 25, 12, 22, 11 };
  int len = 5;

  std::cout << "Original array: ";
  printArray (data1, len);

  // Test selection sort
  selectionSort (data1, len);
  std::cout << "After selection sort: ";
  printArray (data1, len);
  std::cout << "Is sorted: " << (isSorted (data1, len) ? "True" : "False")
            << std::endl;

  // Test bubble sort
  bubbleSort (data2, len);
  std::cout << "After bubble sort: ";
  printArray (data2, len);
  std::cout << "Is sorted: " << (isSorted (data2, len) ? "True" : "False")
            << std::endl;

  // Test insertion sort
  insertionSort (data3, len);
  std::cout << "After insertion sort: ";
  printArray (data3, len);
  std::cout << "Is sorted: " << (isSorted (data3, len) ? "True" : "False")
            << std::endl;

  // Test merge sort
  mergeSort (data4, len);
  std::cout << "After merge sort: ";
  printArray (data4, len);
  std::cout << "Is sorted: " << (isSorted (data4, len) ? "True" : "False")
            << std::endl;

  // Test quick sort
  quickSort (data5, len);
  std::cout << "After quick sort: ";
  printArray (data5, len);
  std::cout << "Is sorted: " << (isSorted (data5, len) ? "True" : "False")
            << std::endl;

  return 0;
}
