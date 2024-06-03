#include <iostream>
#include <random>
#include <chrono>
#include "sorts.h"

using namespace std;

// Функция для замера времени сортировки
double timer(int tip_sort, int a[], long long n) {
    auto start = chrono::high_resolution_clock::now(); // Запуск таймера
    if (tip_sort == 1) {
        selectionSort(a, n);
    } else if (tip_sort == 2) {
        bubbleSort(a, n);
    } else if (tip_sort == 3) {
        insertionSort(a, n);
    } else if (tip_sort == 4) {
        mergeSort(a, n);
    } else {
        quickSort(a, n);
    }
    auto end = chrono::high_resolution_clock::now(); // Окончание таймера
    return chrono::duration_cast<chrono::microseconds>(end - start).count() / 1e6; // Время в секундах
}

int main() {
    setlocale(LC_ALL, "rus"); // Устанавливаем локаль для корректного отображения русских символов
    int m[100000]; // Объявляем массив для тестирования
    long long choice, len; // Переменные для выбора типа сортировки и длины массива
    double time; // Переменная для хранения времени выполнения сортировки

    random_device rd; // Инициализация генератора случайных чисел
    mt19937 gen(rd()); // Создание генератора случайных чисел
    uniform_int_distribution<> dis(0, 100000); // Установка диапазона случайных чисел

    while (true) { // Бесконечный цикл для повторения тестирования
        // Меню для выбора типа сортировки
        cout << "Выберите тип сортировки:\n";
        cout << "(0) Выход\n";
        cout << "(1) Сортировка выбором\n";
        cout << "(2) Пузырьковая сортировка\n";
        cout << "(3) Сортировка вставками\n";
        cout << "(4) Сортировка слиянием\n";
        cout << "(5) Быстрая сортировка\n";
        cout << "Введите ваш выбор: ";
        cin >> choice;

        if (choice == 0)
            return 0;

        cout << "Введите длину тестируемого массива: ";
        cin >> len;

        if (len > 100000) {
            cout << "Длина массива не должна превышать 100000.\n";
            continue;
        }

        // Заполняем массив случайными числами
        for (long long i = 0; i < len; i++)
            m[i] = dis(gen);

        // Замеряем время выполнения сортировки и выводим результат
        time = timer(choice, m, len);
        cout << "Время сортировки: " << time << " секунд\n";
    }
}