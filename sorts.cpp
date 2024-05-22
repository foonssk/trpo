#include <iostream>
// Функция сортировки выбором
void selectionSort(int data[], int lenD)
{
 	int j = 0; // Индекс для поиска минимального элемента
 	int tmp = 0; // Временная переменная для обмена элементов
 	for(int i=0; i<lenD; i++) // Цикл по всем элементам массива
	{
 		j = i; // Начинаем поиск с текущего элемента
 		for(int k = i; k<lenD; k++) // Цикл по неотсортированной части массива
		{
 			if(data[j]>data[k]) // Если текущий элемент больше, чем найденный ранее минимальный
			{
 				j = k; // Обновляем индекс минимального элемента
 			}
 		}
// Меняем местами текущий элемент и минимальный элемент			//Ок, я понял
 	tmp = data[i];
 	data[i] = data[j];
 	data[j] = tmp;
 	}
}

void bubbleSort(int data[], int len)	
{
 	int tmp = 0;
 	for(int i = 0; i < len; i++)	//проход по массиву
 	{
		for(int j = len-1; j >= i+1; j--)	
		{
 			if(data[j] < data[j-1])	//свап элементов
			{						//по условию
 				tmp = data[j];
 				data[j] = data[j-1];
 				data[j-1] = tmp;
 			}
 		}
 	}
}

void insertionSort(int data[], int len)
{
 	int key = 0;
 	int i = 0;
 	for(int j = 1; j < len; j++)	//проход по массиву
	{
 		key = data[j];	//устновка ключа на элемент
 		i = j-1;
 		while(i >= 0 && data[i] > key)	//сдвиг элементов, которые больше
		{								//текущего на одну позицию вправо
 			data[i+1] = data[i];
 			i = i - 1;
 		}
		data[i+1] = key;
 	}
}

void merge(int merged[], int lenD, int L[], int lenL, int R[], int lenR)
{
	а
 	int i = 0;
 	int j = 0;
 	while(i<lenL||j<lenR)
	{
 		if (i<lenL & j<lenR)
		{
 			if(L[i]<=R[j])
			{
 				merged[i+j] = L[i];
 				i++;
 			}
			else
			{
 				merged[i+j] = R[j];
 				j++;
 			}
 		}	
	}