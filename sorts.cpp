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
 		else if(i<lenL)
		{
 			merged[i+j] = L[i];
 			i++;
 		}
 		else if(j<lenR){
 			merged[i+j] = R[j];
 			j++;
 		}
 	}
}

void quickSort(int* data, int const len)
{
 	int const lenD = len;
	int pivot = 0;
 	int ind = lenD/2;
 	int i,j = 0,k = 0;
 	if(lenD>1)
	{
 		int* L = new int[lenD];
 		int* R = new int[lenD];
 		pivot = data[ind];
 		for(i=0;i<lenD;i++)
		{
 			if(i!=ind)
			{
 				if(data[i]<pivot)
				{
 					L[j] = data[i];
 					j++;
 				}
 				else
				{
 					R[k] = data[i];
 					k++;
 				}
 			}
 		}
 		quickSort(L,j);
 		quickSort(R,k);
 		for(int cnt=0;cnt<lenD;cnt++)
		{
 			if(cnt<j)
			{
 				data[cnt] = L[cnt];;
 			}
 			else if(cnt==j)
			{
 				data[cnt] = pivot;
 			}
 			else
			{
 				data[cnt] = R[cnt-(j+1)];
 			}
 		}
	}
}
void mergeSort(int data[], int lenD)
{
 	if(lenD>1)
	{
 		int middle = lenD/2;
 		int rem = lenD-middle;
 		int* L = new int[middle];
 		int* R = new int[rem];
 		for(int i=0;i<lenD;i++)
		{
 			if(i<middle)
			{
 				L[i] = data[i];
 			}
 			else
			{
 				R[i-middle] = data[i];
 			}
 		}
 		mergeSort(L,middle);
 		mergeSort(R,rem);
 		merge(data, lenD, L, middle, R, rem);
 	}
}

