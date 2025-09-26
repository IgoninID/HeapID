// Автор: Игонин В.Ю.

#include <iostream>
#include "MyHeap.h"

using namespace std;

int main()
{
    DynArr<int> arr;
    arr.pushBack(1);
    arr.pushBack(12);
    arr.pushBack(9);
    arr.pushBack(5);
    arr.pushBack(6);
    arr.pushBack(10);
    for (size_t i = 0; i < arr.length(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    HeapSort(arr, arr.length());
    for (size_t i = 0; i < arr.length(); i++)
    {
        cout << arr[i] << " ";
    }
}