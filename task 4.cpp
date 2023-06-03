/* Решение всех задач данного раздела предполагает использование кучи, реализованной в виде шаблонного класса.
Решение должно поддерживать передачу функции сравнения снаружи.
Куча должна быть динамической.

4.3 Планировщик процессов
В операционной системе Technux есть планировщик процессов.
Каждый процесс характеризуется:
приоритетом P
временем, которое он уже отработал t
временем, которое необходимо для завершения работы процесса T
Планировщик процессов выбирает процесс с минимальным значением P * (t + 1), выполняет его время P и кладет обратно в очередь процессов.
Если выполняется условие t >= T, то процесс считается завершенным и удаляется из очереди.
Требуется посчитать кол-во переключений процессора.
Формат входных данных:  Сначала вводится кол-во процессов. После этого процессы в формате P T
Формат выходных данных: Кол-во переключений процессора.
*/

#include <iostream>

using namespace std;

template <typename Type, typename Comparator = less<Type>>
class Heap
{
public:
    Heap();

    //Создание кучи из существующего массива
    Heap(Type *Input, int size){
        Arr = new Type[size];
        copy(Input, Input + size, Arr);

        this->size = size;

        BuildHeap();
    }

    void Insert(Type element){
        Type * temp = new Type[size+1];
        copy(Arr, Arr + size, temp);
        delete[] Arr;

        Arr = temp;
        Arr[size] = element;
        size++;

        SiftUp( size - 1 );
    }

    Type ExtractMax(){
        // Запоминаем значение корня.
        Type result = Arr[0];

        // Переносим последний элемент в корень.
        Type * temp = new Type[size-1];
        copy(Arr + 1, Arr + size, temp);
        delete[] Arr;
        Arr = temp;
        size--;

        // Вызываем SiftDown для корня.
        if( size != 0 ) {
            SiftDown( 0 );
        }
        return result;
    }

    Type PeekMax() const {
        return Arr[0];
    }

    // для вывода интовой кучи
    void PrintIntHeap() {
        int temp = 2;
        for (int i = 0; i < size; i++) {
            cout << Arr[i] << " ";
            if ( i == temp - 2 ) {
                cout << endl;
                temp *= 2;
            }
        }
    }

    int GetSize() {
        return size;
    }

    ~Heap(){
        delete[] Arr;
    }

private:
    Type *Arr;
    int size = 0;
    Comparator cmp = Comparator();

    void BuildHeap(){
        for( int i = size / 2 - 1; i >= 0; --i ) {
            SiftDown( i );
        }
    }
    
    void SiftUp(int index){
        // предок элемента A[i] – элемент A[(i – 1)/2].
        while( index > 0 ) {
            int parent = ( index - 1 ) / 2;
            if( !cmp(Arr[parent], Arr[index]) )
                return;
            swap( Arr[index], Arr[parent] );
            index = parent;
        }
    }

    void SiftDown(int index){
        // потомки элемента A[i] – элементы A[2i + 1] и A[2i + 2].
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        // Ищем большего сына, если такой есть.
        int largest = index;
        if (left < size && cmp(Arr[index], Arr[left]))
            largest = left;
        if (right < size && cmp(Arr[largest], Arr[right]))
            largest = right;

        // Если больший сын есть, то проталкиваем корень в него.
        if (largest != index){
            swap(Arr[index], Arr[largest]);
            SiftDown(largest);
        }
    }
};

//Структура с данными о каждом процессе
struct Process 
{
    public:

        void ReadProcess() {
            cin >> Priority >> Time;
        }

        bool operator()(Process l, Process r)
        {
            if (l.Priority*(l.currentTime + 1) > r.Priority*(r.currentTime + 1)) 
            {
                return true;
            }
            else {
                return false;
            }
        }

        Process operator = (Process proc) {
            this->currentTime = proc.currentTime;
            this->Time = proc.Time;
            this->Priority = proc.Priority;
            return proc;
        }

        int GetCurrentTime() 
        {
            return currentTime;
        }

        int GetPriority() 
        {
            return Priority;
        }

        int GetTime() 
        {
            return Time;
        }

        void SetCurrentTime(int currentTime)
        {
            this->currentTime = currentTime;
        }

        void ProcessPrint() 
        {
            cout << Priority << " " << Time << " " << currentTime << endl;
        }

    private:
        int Priority;
        int currentTime = 0;
        int Time;
};

//Выполнение одного процесса и его постановка обратно в очередь
void ExecOneProcess (Heap<Process, Process>* H) 
{
    Process temp = H->ExtractMax();
    temp.SetCurrentTime(temp.GetCurrentTime() + temp.GetPriority());
    //cout << temp.GetTime() << " " << temp.GetPriority() << " " << temp.GetCurrentTime() << endl;
    if (temp.GetCurrentTime() >= temp.GetTime()) {
        return;
    }
    H->Insert(temp);
}

//Количество переключений процессора во время выполнения очереди процессов
int NumberOfSwitches (Heap<Process, Process>* H) {
    int counter = 0;
    while (H->GetSize() > 0) {
        ExecOneProcess(H);
        counter++;
    }
    return counter;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;

    Process* Arr = new Process [n];
    for (int i=0; i<n; i++) {
        Arr[i].ReadProcess();
    }
    
    Heap<Process, Process> H(Arr, n);

    cout << NumberOfSwitches(&H);
 
    return 0;
}

/*  Создание кучи: T(n)=O(n), M(n)=O(n);
    Выполнение одного процесса: T(n)=O(log n + log n) = O(2log n), M(n)=O(n);
    Выполнение всей очереди процессов: T(n)=O(2m log n), M(n)=O(n), где m - кол-во переключений процессора; */
              