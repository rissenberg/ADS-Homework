/* Дано множество целых чисел из [0..10^9] размера n. 
Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
10%  перцентиль
медиана
90%  перцентиль

Требования: к дополнительной памяти: O(n) (????)
Среднее время работы: O(n)
Должна быть отдельно выделенная функция partition. 
Рекурсия запрещена. 
Решение должно поддерживать передачу функции сравнения снаружи.

6_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”. 
Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
*/

#include <iostream>

using namespace std;

template <typename Type, typename Comparator = less<Type>>
int Partition (Type Arr[], int left, int right, int pivot, Comparator cmp = Comparator()) 
{
    int j = left;
    int i = left;
    int k = left;
    Type key = Arr[pivot];
    swap (Arr[pivot], Arr[right-1]); // перемещение опорного в конец
    for (int j = left; j < right-1; j++) {
        if (cmp (Arr[j], key)) {
            swap (Arr[i], Arr[j]);
            i++;
        }
    }
    swap (Arr[right-1], Arr[i]); // возвращение опорного на место

    return i;
}

template <typename Type, typename Comparator = less<Type>>
Type QuickSelect (Type* Arr, int size, int k, Comparator cmp = Comparator())
{
    int left = 0;
    int right = size;
    int pivot;

    while (right - left > 0) {
        pivot = (right + left) / 2 ;
        // расстановка относительно опорного элемента pivot 
        pivot = Partition (Arr, left, right, pivot);
        if (pivot == k) {
            return Arr[pivot];
        }
        if (pivot > k) {
            right = pivot;
        }
        else {
            left = pivot + 1;
        }
    }
    // возврат при ошибке
    return -1;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;

    int* Arr = new int [n];
    for (int i = 0; i < n; i++) {
        cin >> Arr[i];
    }

    cout << QuickSelect (Arr, n, n*0.1) << endl; // 10%  перцентиль
    cout << QuickSelect (Arr, n, n*0.5) << endl; // 50%  перцентиль (медиана)
    cout << QuickSelect (Arr, n, n*0.9) << endl; // 90%  перцентиль

    delete[] Arr;

    return 0;
}

/*  Выполнение функции Partition: T(n)=O(n), M(n)=O(1);
    Выполнение функции QuickSelect: T(n)=O(n + n/2 + n/4 + ...) = O(2n), M(n)=O(1); */
              