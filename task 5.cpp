/* Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием в виде шаблонной функции. 
Решение должно поддерживать передачу функции сравнения снаружи.
Общее время работы алгоритма O(n log n).
5_4. Закраска прямой 2.
На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого отрезка (Li и Ri). Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.
*/

#include <iostream>

using namespace std;

template <typename Type, typename Comparator = less<Type>>
void Merge(Type Arr[], int sizeLeft, int size, Type Aux[], Comparator cmp)
{
    int k = 0;
    int i = 0; 
    int j = sizeLeft;
 
    while (i < sizeLeft && j < size)
    {
        if ( cmp(Arr[i], Arr[j]) ) {
            Aux[k] = Arr[i];
            k++;
            i++;
        }
        else {
            Aux[k] = Arr[j];
            k++;
            j++;
        }
    }
    // копируем оставшиеся элементы
    copy(Arr + i, Arr + sizeLeft, Aux + k);
    copy(Arr + j, Arr + size, Aux + k);
    // копируем из вспомогательного массива в соновной
    copy(Aux, Aux + size, Arr);
}

template <typename Type, typename Comparator = less<Type>>
void MergeSort (Type* Arr, int size, Comparator cmp)
{
    if (size <= 1) {
        return;
    }
    int sizeLeft = size /2;
    int sizeRight = size - sizeLeft;

    // сортировка для левой и правой половины массива
    MergeSort (Arr, sizeLeft, cmp);
    MergeSort (Arr + sizeLeft, sizeRight, cmp);

    // слияние двух подмассивов
    Type* Aux = new Type[size];
    Merge (Arr, sizeLeft, size, Aux, cmp);
    delete[] Aux;
}

struct Paint 
{
    int coord; // координата начала/конца закрашенного отрезка
    bool state; // состояние: 1 - начало отрезка, 0 - конец
};

// функция сравнения координат
bool PaintCompLess(Paint l, Paint r)
{
    if (l.coord < r.coord) 
    {
        return true;
    }
    else {
        return false;
    }
}

int LengthOfSingleLayer (Paint* Arr, int size) 
{
    int layers = 1;
    int length = 0;
    for (int i = 1; i < size; i++) {
        if (layers == 1) {
            length += Arr[i].coord - Arr[i-1].coord;
        }
        if (Arr[i].state) {
            layers++;
        } else {
            layers--;
        }
    }
    return length;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;

    Paint* Arr = new Paint [n*2];
    for (int i = 0; i < n; i++) {
        cin >> Arr[i*2].coord;
        Arr[i*2].state = 1;
        cin >> Arr[i*2+1].coord;
        Arr[i*2+1].state = 0;
    }
    n *= 2;

    MergeSort (Arr, n, PaintCompLess);

    // Поиск длинны, закрашенной ровно в один слой
    cout << LengthOfSingleLayer(Arr, n);

    delete[] Arr;

    return 0;
}

/*  Выполнение функции Merge: T(n)=O(n), M(n)=O(1);
    Выполнение функции MergeSort: T(n)=O(n * log n), M(n)=O(n); 
    Выполнение функции LengthOfSingleLayer: T(n)=O(n), M(n)=O(1);*/
              