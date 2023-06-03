/* Задано N точек на плоскости. Указать (N-1)-звенную несамопересекающуюся замкнутую ломаную, проходящую через все эти точки.
Предполагается, что никакие три точки не лежат на одной прямой.
Стройте ломаную от точки, имеющей наименьшую координату x. Если таких точек несколько, то используйте точку с наименьшей координатой y. Точки на ломаной расположите в порядке убывания углов лучей от начальной точки до всех остальных точек.
Для сортировки точек реализуйте алгоритм сортировки вставками.
*/
#include <iostream>
#include <string>

using namespace std;

template <typename Type, typename Comparator = less<Type>>
void InsertSort(Type* Arr, int size, Comparator cmp) {
	Type temp;
	for (int i = 0; i < size; i++) {
		temp = Arr[i];
        int j;
 
		for (j = i - 1; j >= 0 && cmp (temp, Arr[j]); j--) {
            Arr[j+1] = Arr[j];
        }
		Arr[j+1] = temp;
	}
}

struct Point 
{
    int x;
    int y;
};

// функция сравнения координат
bool PointCompLess(Point l, Point r)
{
    if (l.x < r.x) 
    {
        return true;
    }
    else {
        if (( l.x == r.x) && (l.y < r.y)) {
            return true;
        }
    }
    return false;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    
    cin >> n;

    Point *Arr = new Point [n];

    for (int i = 0; i < n; i++) {
        cin >> Arr[i].x >> Arr[i].y;
    }

    InsertSort(Arr, n, PointCompLess);
    
    for (int i = 0; i < n; i++) {
        cout << Arr[i].x << " " << Arr[i].y << endl;
    }

    delete [] Arr;

    return 0;
}