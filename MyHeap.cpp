// Автор: Игонин В.Ю.

#include "MyHeap.h"
#include <cassert>

using namespace std;

void test()
{
	// вставка, удаление, размер, проверка на пустую кучу, поиск в пустой, из одного, 5 элементов куч
	{
		MyHeap<int> heap;
		MyHeap<int> heap1;
		MyHeap<int> heap5;
		assert(heap.empty());
		assert(heap.getSize() == 0);
		try
		{
			heap.Max();
			assert(false);
		}
		catch (runtime_error&)
		{

		}
		try
		{
			heap.Find(5);
			assert(false);
		}
		catch (runtime_error&)
		{

		}
		try
		{
			heap.Remove();
			assert(false);
		}
		catch (runtime_error&)
		{

		}

		heap1.Insert(1);
		assert(!heap1.empty());
		assert(heap1.getSize() == 1);
		assert(heap1.Max() == 1);
		assert(heap1.Find(1) == 0);
		try
		{
			heap1.Find(5);
			assert(false);
		}
		catch (overflow_error&)
		{

		}
		heap1.Remove();
		assert(heap1.empty());


		heap5.Insert(1);
		heap5.Insert(2);
		heap5.Insert(3);
		heap5.Insert(4);
		heap5.Insert(5);
		assert(!heap5.empty());
		assert(heap5.getSize() == 5);
		assert(heap5.Max() == 5);
		assert(heap5.Find(1) == 3);
		assert(heap5.Find(5) == 0);
		assert(heap5.Find(3) == 4);
		try
		{
			heap5.Find(6);
			assert(false);
		}
		catch (overflow_error&)
		{

		}
		heap5.Remove();
		try
		{
			heap5.Find(5);
			assert(false);
		}
		catch (overflow_error&)
		{

		}
		assert(heap5.Find(4) == 0);
	}

	// сортировка кучей (пустой массив, 1, 5 элементов массива)
	{
		DynArr<int> arr;
		DynArr<int> arr1;
		arr1.pushBack(5);
		DynArr<int> arr5;
		arr5.pushBack(3);
		arr5.pushBack(7);
		arr5.pushBack(1);
		arr5.pushBack(20);
		arr5.pushBack(15);

		HeapSort(arr);
		HeapSort(arr1);
		HeapSort(arr5);

		assert(arr.length() == 0);
		assert(arr1[0] == 5);
		assert(arr5[0] == 20);
		assert(arr5[1] == 15);
		assert(arr5[2] == 7);
		assert(arr5[3] == 3);
		assert(arr5[4] == 1);
	}

	// итератор кучи
	{

	}

}