/* ВНИМАНИЕ! Для решения данной задачи нужно использовать структуру данных стек!
Дана последовательность, состоящая из символов '(' и ')'. 
Требуется определить, является ли данная последовательность правильной 
скобочной последовательностью. Длина исходной последовательности ≤ 800000.
*/
#include <iostream>
#include <string>

using namespace std;

class Stack{
    public:
        Stack() {}
        
        void push (int element) {
            // Если не хватает места, увеличиваем буфер
            if (size == buffer) {
                ExtendBuffer();
            }
            
            Arr[pointer] = element;
            pointer++;
            size++;
        }

        int pop () {
            if (size == 0) {
                return -1;
            }

            int t = Arr[pointer];
            Arr[pointer] = 0;
            pointer--;
            size--;

            return t;
        }

        int GetSize() {
            return size;
        }

        ~Stack() {
            delete [] Arr;
        }

    private:
        int *Arr = new int[8]; // Массив, хранящий элементы очереди
        int size = 0; // Колво элементов
        int buffer = 8; // Рабочий размер очереди, мб увеличен
        int pointer = 0;

        void ExtendBuffer() {
            // Создаем вспомогательный массив в 2 раза большей длины и копируем очередь в него
            int * t = new int[buffer*2];

            copy(Arr, Arr + pointer, t);
    
            delete[] Arr;

            buffer *= 2;
            Arr = t;
        }

};

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string input;
    cin >> input;

    Stack S;

    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '(') {
            S.push(1);
        }
        else {
            if (S.pop() == -1) {
                cout << "NO";
                return 0;
            }
        }
    }

    if (S.GetSize() != 0) {
        cout << "NO";
        return 0;
    }
    
    cout << "YES";
    return 0;
}