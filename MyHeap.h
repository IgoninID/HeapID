// �����: ������ �.�.

#pragma once
#include "../TemplArr/Arr.h"
#include "../InterfIter/AbstrIter.h"

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

    class Iterator : public AbstrIter<T>
    {
        MyHeap<T>* heapPtr;
        size_t i;

    public:
        Iterator(MyHeap<T>* heap, size_t i) : heapPtr(heap), i(i) {}
        Iterator& operator ++() override
        {
            ++i;
            return *this;
        }

        T& operator *() const override
        {
            if (i >= heapPtr->getSize())
            {
                throw out_of_range("�� ��������� ����");
            }
            return heapPtr->arr[i];
        }

        bool operator !=(const AbstrIter<T>& other) const override
        {
            const Iterator* it = dynamic_cast<const Iterator*>(&other);
            return !it || this->i != it->i || this->heapPtr != it->heapPtr;
        }
    };

    Iterator begin()
    {
        return Iterator(this, 0);
    }

    Iterator end()
    {
        return Iterator(this, size);
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
            size = 0;
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

};

/// <summary>
/// ���������� ����� (�� ��������)
/// ��������� �(n log n)
/// </summary>
/// <typeparam name="T">��� ������</typeparam>
/// <param name="arr">����������� ������</param>
template <typename T>
void HeapSort(DynArr<T>& arr)
{
    size_t size = arr.length();
    if (size <= 1)
    {
        return;
    }
    MyHeap<T> heap(arr);
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = heap.Max();
        heap.Remove();
    }
}

/// <summary>
/// ����� ������� ����
/// </summary>
void test();