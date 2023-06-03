/* Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
Формат входных данных.
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”. 
Формат выходных данных.
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

3_1. Реализовать очередь с динамическим зацикленным буфером.
Требования: Очередь должна быть реализована в виде класса.
*/

#include <iostream>

using namespace std;

class Queue{
    public:
        Queue() {}
        
        void push (int element) {
            // Если не хватает места, увеличиваем буфер
            if (size == buffer) {
                ExtendBuffer();
            }
            
            Arr[tail] = element;
            tail++;
            size++;

            //Если указатель tail вышел за пределы буфера, зацикливаем его в начало
            if ((tail >= buffer)&&(size != buffer)) {
                tail = 0;
            }

        }

        int pop () {
            //Проверка на пустую очередь
            if (size == 0) {
                return -1;
            }

            int t = Arr[head];
            Arr[head] = 0;
            head++;
            size--;

            //Если указатель вышел за пределы буфера, возвращаем его в начало
            if (head == buffer) {
                head = 0;
            }

            return t;
        }

        /* Отладка программы
        void ShowQueue() {
            for (int i = 0; i < buffer; i++) {
                cout << Arr[i] << " ";
            }
        } */

        ~Queue() {
            delete [] Arr;
        }

    private:
        int *Arr = new int[8]; // Массив, хранящий элементы очереди
        int size = 0; // Колво элементов
        int buffer = 8; // Рабочий размер очереди, мб увеличен
        int head = 0; // Указатель на первый элемент
        int tail = 0; // Указатель на место, куда будет помещен следующий элемент

        void ExtendBuffer() {
            // Создаем вспомогательный массив в 2 раза большей длины и копируем очередь в него
            int * t = new int[buffer*2];
    
            if (head < tail) {
                copy(Arr + head, Arr + tail, t);
            }
            else {
                copy(Arr + head, Arr + buffer, t);
                copy(Arr, Arr + tail, t + buffer - head);
            }
    
            delete[] Arr;

            head = 0;
            tail = size;
            buffer *= 2;
            Arr = t;
        }

};

// Непосредственно сама задача - проверка тестов на правильность ожидаемого вывода
bool AreExpectationsTrue (int &n, Queue* Q) {
    int com, elem;
    for (int i = 0; i < n; i++) {
        cin >> com >> elem;
        if (com == 3) {
            Q->push(elem);
        }
        else {
            if (Q->pop() != elem) {
                return false;
            }
        }
    }
    return true;
}

int main() 
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    Queue* Q = new Queue;

    int n;
    cin >> n;

    if (AreExpectationsTrue(n, Q)) {
         cout << "YES";
    } 
    else {
        cout << "NO";
    }

    return 0;
}

/* Для метода pop: T(n)=O(1), M(n)=O(1);
              push: T(n)=O(1), M(n)=O(1) - в лучшем случае,
                    T(n)=O(n), M(n)=O(n) - в случае увеличения буффера. */