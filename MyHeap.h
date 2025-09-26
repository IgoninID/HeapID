// Автор: Игонин В.Ю.

#pragma once
#include "../TemplArr/Arr.h"

template <typename T>
void HeapMake(DynArr<T>& arr, size_t size, size_t i)
{
	size_t large = i;
	size_t left = 2 * i + 1;
	size_t right = 2 * i + 2;
	if (left < size && arr[left] > arr[large])
	{
		large = left;
	}
	if (right < size && arr[right] > arr[large])
	{
		large = right;
	}
	if (large != i)
	{
		swap(arr[i], arr[large]);
		//T temp = arr[i];
		//arr[i] = arr[large];
		//arr[large] = temp;
		HeapMake(arr, size, large);
	}
}

template <typename T>
void HeapSort(DynArr<T>& arr, size_t size)
{
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		HeapMake(arr, size, i);
	}
	for (int i = size - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);
		HeapMake(arr, i, 0);
	}
}

void test();