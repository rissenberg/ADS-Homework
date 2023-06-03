/* 7_1. MSD для строк.
Дан массив строк. Количество строк не больше 105. Отсортировать массив методом поразрядной сортировки MSD по символам.
Размер алфавита - 256 символов. Последний символ строки = ‘\0’.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;


void CountingSortStr (string Arr[], int const left, int const right, int const index) 
{
   char minVal = Arr[left][index];
   char maxVal = Arr[left][index];

   for (int i = left+1; i < right; i++) {
        if (Arr[i][index] != '\0') {
            minVal = min(minVal, Arr[i][index]);
            maxVal = max(maxVal, Arr[i][index]);
        }
        else {
            minVal = -1;
        }
   }

   int countBufSize = int (maxVal) - int(minVal) + 1;
   int *countBuf = new int[countBufSize];

    for (int i = left; i < right; i++) {
        if (Arr[i][index] != '\0') {
            countBuf[Arr[i][index] - minVal]++;
        }
        else {
            countBuf[0]++;
        }
    }

    char* tempBuf = new char[right];

    for (int i = 1; i< countBufSize; i++) {
        countBuf[i] += countBuf[i-1];
    }

    for (int i = right - 1; i >= left; i--) {
        int countBufPos = Arr[i][index] - minVal;
        countBuf[countBufPos]--;
        tempBuf[countBuf[countBufPos]] = Arr[i][index];
    }

    for (int i = left; i < right; i++) {
        Arr[i][index] = tempBuf[i];
    }

   delete [] countBuf;
   delete [] tempBuf;
}

void MSDStr (string Arr[], int const left, int const right, int const index) 
{   
    cout << left << " " << right << endl << endl;
    if ((right - left < 2)) {
        cout << "RETURN \n";
        return;
    }
    CountingSortStr(Arr, left, right, index);

    for (int i = 0; i < right; i++) {
        cout << Arr[i] << endl;
    }

    int i = 0;
    int leftRec = 0;
    int rightRec = 0;
    while (i < right) {
        i++;
        while ((i < right) && (Arr[i][index] == Arr[i-1][index])) {
            i++;
        }
        rightRec = i;
        MSDStr(Arr, leftRec, rightRec, index + 1);
        leftRec = i;
    }
    
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    vector<string> Input;
    string input;
    while (cin >> input) {
        Input.push_back(input);
    }

    string* Arr = new string[Input.size()];
    for (int i = 0; i < Input.size(); i++) {
        Arr[i] = Input[i];
    }
    int size = Input.size();

    MSDStr(Arr, 0, size, 0);

    for (int i = 0; i < size; i++) {
        cout << Arr[i] << endl;
    }

    delete [] Arr;
    return 0;
}

/*  Выполнение функции Partition: T(n)=O(n), M(n)=O(1);
    Выполнение функции QuickSelect: T(n)=O(n + n/2 + n/4 + ...) = O(2n), M(n)=O(1); */
              