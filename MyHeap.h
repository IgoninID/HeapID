// Автор: Игонин В.Ю.

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

// Шаблонный класс MyHeap, реализующий структуру данных "максимальная куча" (max-heap)
template <typename T>
class MyHeap
{
private:
    DynArr<T> arr; // Динамический массив для хранения элементов кучи
    size_t size;   // Текущий размер кучи (количество элементов)

    /// <summary>
    /// Поднимает элемент с указанным индексом вверх по куче, чтобы восстановить свойство кучи.
    /// </summary>
    /// <param name="ind">Индекс элемента, который нужно поднять.</param>
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
    /// Опускает элемент с указанным индексом вниз по куче, чтобы восстановить свойство кучи.
    /// </summary>
    /// <param name="ind">Индекс элемента, который нужно опустить.</param>
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
    /// Конструктор по умолчанию. Создает пустую кучу.
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
                throw out_of_range("За пределами кучи");
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
    /// Конструктор, создающий кучу из динамического массива.
    /// </summary>
    /// <param name="arr">Динамический массив, на основе которого создается куча.</param>
    MyHeap(const DynArr<T>& arr) : arr(arr)
    {
        this->size = arr.length();
        for (long long i = this->size / 2 - 1; i >= 0; i--)
        {
            down(i);
        }
    }

    /// <summary>
    /// Возвращает ссылку на внутренний массив кучи.
    /// </summary>
    /// <returns>Ссылка на динамический массив, содержащий элементы кучи.</returns>
    DynArr<T>& getArr()
    {
        return arr;
    }

    /// <summary>
    /// Возвращает текущий размер кучи.
    /// </summary>
    /// <returns>Количество элементов в куче.</returns>
    size_t getSize() const
    {
        return size;
    }

    /// <summary>
    /// Возвращает максимальный элемент кучи (корень).
    /// </summary>
    /// <returns>Ссылка на максимальный элемент кучи.</returns>
    /// <exception cref="runtime_error Выбрасывается, если куча пуста."></exception>
    T& Max()
    {
        if (empty()) throw runtime_error("Куча пустая");
        return arr[0];
    }

    /// <summary>
    /// Вставляет новый элемент в кучу.
    /// </summary>
    /// <param name="data">Элемент, который нужно вставить.</param>
    void Insert(T data)
    {
        arr.pushBack(data);
        size += 1;
        up(size - 1);
    }

    /// <summary>
    /// Проверяет, пуста ли куча.
    /// </summary>
    /// <returns>Возвращает true, если куча пуста, иначе false.</returns>
    bool empty() const
    {
        return size == 0;
    }

    /// <summary>
    /// Удаляет максимальный элемент из кучи.
    /// </summary>
    /// <exception cref="runtime_error Выбрасывается, если куча пуста."></exception>
    void Remove()
    {
        if (empty()) throw runtime_error("Куча пустая");
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
    /// Ищет элемент в куче и возвращает его индекс.
    /// </summary>
    /// <param name="data">Элемент, который нужно найти.</param>
    /// <returns>Индекс найденного элемента.</returns>
    /// <exception cref="runtime_error Выбрасывается, если куча пуста."></exception>
    /// <exception cref="overflow_error Выбрасывается, если элемент не найден."></exception>
    size_t Find(T data)
    {
        if (empty()) throw runtime_error("Куча пустая");
        for (size_t i = 0; i < size; i++)
        {
            if (arr[i] == data)
            {
                return i;
            }
        }
        throw overflow_error("Нет такого элемента");
    }

};

/// <summary>
/// Сортировка кучей (по убыванию)
/// Сложность О(n log n)
/// </summary>
/// <typeparam name="T">Тип данных</typeparam>
/// <param name="arr">Сортируемый массив</param>
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
/// Тесты методов кучи
/// </summary>
void test();