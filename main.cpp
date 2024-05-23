#include <iostream>
#include <ctime>
#include <random>
#include "sorts.h"

using namespace std;
// Функция для замера времени сортировки
double timer(int tip_sort, int a[], long long n)
{
    unsigned int start = clock(); //выбор сортировки 
	if (tip_sort == 1)
	{
	selectionSort(a, n);
	}
	else if (tip_sort == 2)
	{
	bubbleSort(a, n);
	}
	else if (tip_sort == 3)
	{
	insertionSort(a, n);
	}
	else if (tip_sort == 4)
	{
	mergeSort(a, n);
	}
	else
	{
	quickSort(a, n);
	}
	return (clock() - start) / 1000.0; //время в сек
    }

int main()
{
    setlocale(LC_ALL, "rus"); // Устанавливаем локаль для корректного отображения русских символов
    int m[100000]; // Объявляем массив для тестирования
	long long choice, len; // Переменные для выбора типа сортировки и длины массива
	double time; // Переменная для хранения времени выполнения сортировки

    while (true) // Бесконечный цикл для повторения тестирования
	{
        // меню для выбора типа сортировки
		cout << "Select the sort type:\n(0) exit\n(1) Sorting by choice\n(2)";
		cin >> choice;

		if (choice == 0)
		return 0;
        cout << "Write the length of the array under test:\n";// выбор длины тестируемого массива
		cin >> len;

        // Заполняем массив случайными числами
		for (long long i = 0; i < len; i++)
		m[i] = rand();

        // Замеряем время выполнения сортировки и выводим результат
		cout << timer(choice, m, len) << "s\n";
    }
}