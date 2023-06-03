/* 2_1. Дан отсортированный массив целых чисел A[0..n-1] и массив 
целых чисел B[0..m-1]. Для каждого элемента массива B[i] найдите 
минимальный индекс k минимального элемента массива A, равного 
или превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет, 
выведите n. n, m ≤ 10000.
Требования:  Время работы поиска k для каждого элемента B[i]: O(log(k)). 
Внимание! В этой задаче для каждого B[i] сначала нужно определить 
диапазон для бинарного поиска размером порядка k с помощью 
экспоненциального поиска, а потом уже в нем делать бинарный поиск.
Формат входных данных.
В первой строчке записаны числа n и m. Во второй и третьей 
массивы A и B соответственно.
*/

#include <iostream>

using namespace std;

short int MinimumIndex(int* Arr, short int* size, int key) {
    //проверка на дурочка
    if (*size == 0) {
        return 0;
    }
    //экспоненциальный поиск области
    int k = 1;
    if (Arr[0] >= key) {
        return 0;
    }
    while ((k < *size) && (Arr[k] < key)) {
        k *= 2;
    }
    if ((k > *size - 1)&&(Arr[*size - 1] < key)) { 
    	return *size;
    }
    //бинарный поиск по выбранной области
    short int l = k/2;
    short int r;
	if (k > *size - 1) { 
    	r = *size - 1;
    } else {
        r = k;
    }
    short int mid;
 
    while (l <= r) {
    	mid = l + (r - l) / 2;
 
    	if ((Arr[mid] >= key) && (Arr[mid-1]<key)) {
            return mid;
        }
    	if (Arr[mid] >= key) {
            r = mid - 1;
        }
    	else {
            l = mid + 1;
        }
    }

    return mid;
};

int main() 
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    short int n, m;
    
    cin >> n >> m;

    int *A = new int[n];
    int *B = new int[m];

    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> B[i];
    }

    for (int i = 0; i < m; i++) {
        cout << MinimumIndex(A, &n, B[i]) << " ";
    }

    delete [] A;
    delete [] B;

    return 0;
}

// Для поиска каждого индекса: T(n)=O(log(k)+log(k/2))=O(log(k)), M(n)=O(1), где k - искомый индекс