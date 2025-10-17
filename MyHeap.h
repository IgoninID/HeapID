// �����: ������ �.�.

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

// ��������� ����� MyHeap, ����������� ��������� ������ "������������ ����" (max-heap)
template <typename T>
class MyHeap
{
private:
    DynArr<T> arr; // ������������ ������ ��� �������� ��������� ����
    size_t size;   // ������� ������ ���� (���������� ���������)

    /// <summary>
    /// ��������� ������� � ��������� �������� ����� �� ����, ����� ������������ �������� ����.
    /// </summary>
    /// <param name="ind">������ ��������, ������� ����� �������.</param>
    void up(size_t ind)
    {
        while (ind > 0)
        {
            size_t par = (ind - 1) / 2;
            if (arr[ind] > arr[par])
            {
                swap(arr[ind], arr[par]);
                ind = par;
            }
            else
            {
                break;
            }
        }
    }

    /// <summary>
    /// �������� ������� � ��������� �������� ���� �� ����, ����� ������������ �������� ����.
    /// </summary>
    /// <param name="ind">������ ��������, ������� ����� ��������.</param>
    void down(size_t ind)
    {
        while (true)
        {
            size_t left = 2 * ind + 1;
            size_t right = 2 * ind + 2;
            size_t large = ind;
            if (left < size && arr[left] > arr[large])
            {
                large = left;
            }
            if (right < size && arr[right] > arr[large])
            {
                large = right;
            }
            if (large != ind)
            {
                swap(arr[ind], arr[large]);
                ind = large;
            }
            else
            {
                break;
            }
        }
    }

public:
    /// <summary>
    /// ����������� �� ���������. ������� ������ ����.
    /// </summary>
    MyHeap()
    {
        size = 0;
    }

    /// <summary>
    /// �����������, ��������� ���� �� ������������� �������.
    /// </summary>
    /// <param name="arr">������������ ������, �� ������ �������� ��������� ����.</param>
    MyHeap(const DynArr<T>& arr) : arr(arr)
    {
        this->size = arr.length();
        for (long long i = this->size / 2 - 1; i >= 0; i--)
        {
            down(i);
        }
    }

    /// <summary>
    /// ����������� �����������. ������� ���� �� ������ ������ ����.
    /// </summary>
    /// <param name="heap">����, �� ������� ���������� ������.</param>
    MyHeap(const MyHeap<T>& heap) : arr(heap.arr)
    {
        this->size = heap.size;
    }

    /// <summary>
    /// ����������� �����������. ��������� ������ �� ������ ����.
    /// </summary>
    /// <param name="heap">����, �� ������� ����������� ������.</param>
    MyHeap(MyHeap<T>&& heap) noexcept : arr(heap.arr)
    {
        this->size = heap.size;
        heap.size = 0;
        heap.arr.Clear();
    }

    /// <summary>
    /// �������� ������������ (�����������).
    /// </summary>
    /// <param name="heap">����, �� ������� ���������� ������.</param>
    /// <returns>������ �� ������� ���� ����� ������������.</returns>
    MyHeap<T>& operator = (const MyHeap<T>& heap)
    {
        return MyHeap(heap);
    }

    /// <summary>
    /// �������� ������������ (�����������).
    /// </summary>
    /// <param name="heap">����, �� ������� ����������� ������.</param>
    /// <returns>������ �� ������� ���� ����� ������������.</returns>
    MyHeap<T>& operator = (MyHeap<T>&& heap)
    {
        if (this != &heap)
        {
            return MyHeap(heap);
        }
        return *this;
    }

    /// <summary>
    /// ���������� ������ �� ���������� ������ ����.
    /// </summary>
    /// <returns>������ �� ������������ ������, ���������� �������� ����.</returns>
    DynArr<T>& getArr()
    {
        return arr;
    }

    /// <summary>
    /// ���������� ������� ������ ����.
    /// </summary>
    /// <returns>���������� ��������� � ����.</returns>
    size_t getSize() const
    {
        return size;
    }

    /// <summary>
    /// ���������� ������������ ������� ���� (������).
    /// </summary>
    /// <returns>������ �� ������������ ������� ����.</returns>
    /// <exception cref="runtime_error �������������, ���� ���� �����."></exception>
    T& Max()
    {
        if (empty()) throw runtime_error("���� ������");
        return arr[0];
    }

    /// <summary>
    /// ��������� ����� ������� � ����.
    /// </summary>
    /// <param name="data">�������, ������� ����� ��������.</param>
    void Insert(T data)
    {
        arr.pushBack(data);
        size += 1;
        up(size - 1);
    }

    /// <summary>
    /// ���������, ����� �� ����.
    /// </summary>
    /// <returns>���������� true, ���� ���� �����, ����� false.</returns>
    bool empty() const
    {
        return size == 0;
    }

    /// <summary>
    /// ������� ������������ ������� �� ����.
    /// </summary>
    /// <exception cref="runtime_error �������������, ���� ���� �����."></exception>
    void Remove()
    {
        if (empty()) throw runtime_error("���� ������");
        if (size == 1)
        {
            arr.popFront();
            return;
        }
        arr[0] = arr[size - 1];
        arr.popBack();
        down(0);
        size -= 1;
    }

    /// <summary>
    /// ���� ������� � ���� � ���������� ��� ������.
    /// </summary>
    /// <param name="data">�������, ������� ����� �����.</param>
    /// <returns>������ ���������� ��������.</returns>
    /// <exception cref="runtime_error �������������, ���� ���� �����."></exception>
    /// <exception cref="overflow_error �������������, ���� ������� �� ������."></exception>
    size_t Find(T data)
    {
        if (empty()) throw runtime_error("���� ������");
        for (size_t i = 0; i < size; i++)
        {
            if (arr[i] == data)
            {
                return i;
            }
        }
        throw overflow_error("��� ������ ��������");
    }

    /// <summary>
    /// ����������. ����������� ������, ������� �����.
    /// </summary>
    ~MyHeap()
    {
        arr.Clear();
    }
};


void test();