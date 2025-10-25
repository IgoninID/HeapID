// �����: ������ �.�.

#include "MyHeap.h"
#include <cassert>

using namespace std;

/// <summary>
/// ����� ������� ����
/// </summary>
void test()
{
	// �������, ��������, ������, �������� �� ������ ����, ����� � ������, �� ������, 5 ��������� ���
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

	// ���������� ����� (������ ������, 1, 5 ��������� �������)
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

		DynArr<int> arr_inc;
		arr_inc.pushBack(1);
		arr_inc.pushBack(2);
		arr_inc.pushBack(5);
		arr_inc.pushBack(20);
		arr_inc.pushBack(30);

		DynArr<int> arr_dec;
		arr_dec.pushBack(30);
		arr_dec.pushBack(20);
		arr_dec.pushBack(5);
		arr_dec.pushBack(2);
		arr_dec.pushBack(1);

		HeapSort(arr);
		HeapSort(arr1);
		HeapSort(arr5);
		HeapSort(arr_inc);
		HeapSort(arr_dec);

		assert(arr.length() == 0);

		assert(arr1[0] == 5);

		assert(arr5[0] == 20);
		assert(arr5[1] == 15);
		assert(arr5[2] == 7);
		assert(arr5[3] == 3);
		assert(arr5[4] == 1);

		assert(arr_inc[0] == 30);
		assert(arr_inc[1] == 20);
		assert(arr_inc[2] == 5);
		assert(arr_inc[3] == 2);
		assert(arr_inc[4] == 1);

		assert(arr_dec[0] == 30);
		assert(arr_dec[1] == 20);
		assert(arr_dec[2] == 5);
		assert(arr_dec[3] == 2);
		assert(arr_dec[4] == 1);
	}

	// �������� ����
	{

	}

}