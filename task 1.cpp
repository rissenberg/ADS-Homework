/* 1. Хеш-таблица
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
1_1. Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
Требования: В таблице запрещено хранение указателей на описатель элемента.
*/

#include <iostream>
#include <vector>

using namespace std;

const size_t DEFAULT_SIZE = 8;

template <typename T>
struct HashtableNode
{
    HashtableNode()
    {
    }

    HashtableNode(const bool flag)
    : deleted(flag)
    {
    }
    
    HashtableNode(const T &data)
    : data(data), deleted(false)
    {
    }

    ~HashtableNode()
    {
    }
    
    T data;
    bool deleted;
};

class StringHasher
{
public:
    StringHasher(size_t prime = 71)
    : prime(prime) 
    {
    }
    
    ~StringHasher()
    {
    }

    size_t operator()(const string &str)
    {
        size_t hash = 0;
        for (size_t i = 0; i < str.size(); ++i)
        {
            hash = hash * prime + str[i];
        }
        return hash;
    }
    
private:
    size_t prime;
};

template <typename T, typename Hasher>
class Hashtable
{
public:
    Hashtable(size_t initial_size = DEFAULT_SIZE)
    : size(0), table(initial_size, nullptr)
    {
    }
    
    ~Hashtable()
    {
    }
    
    bool Add(const T &key)
    {
        if (size >= table.size() * 0.75)
        {
            grow();
        }
        
        size_t hash = hasher(key) % table.size();
        for (int i = 0; i < table.size(); i++)
        {
            size_t hash_try = (hash + i) % table.size();
            if (!table[hash_try])
            {
                table[hash_try] = new HashtableNode<T>(key);
                size++;
                return true;
            }
            if (table[hash_try]->data == key)
            {
                return false;
            }
        }

        for (int i = 0; i < table.size(); i++)
        {
            size_t hash_try = (hash + i) % table.size();

            if (table[hash_try]->deleted)
            {
                table[hash_try]->data = key;
                table[hash_try]->deleted = false;
                size++;
                return true;
            }
        }
        cout << "!";
        return false;
    }
    
    bool Has(const T &key)
    {
        size_t hash = hasher(key) % table.size();
        for (int i = 0; i < table.size(); i++)
        {
            size_t hash_try = (hash + i) % table.size();
            if (!table[hash_try])
            {
                return false;
            }
            if (table[hash_try]->data == key)
            {
                return true;
            }
        }

        return false;
    }
    
    bool Delete(const T &key)
    {
        size_t hash = hasher(key) % table.size();
        
        for (int i = 0; i < table.size(); i++)
        {
            size_t hash_try = (hash + i) % table.size();
            if (!table[hash_try])
            {
                return false;
            }
            if (table[hash_try]->data == key)
            {
                delete table[hash_try];
                table[hash_try] = new HashtableNode<T>(true);
                size--;
                return true;
            }
        }

        return false;
    }
    
private:
    void grow()
    {
        vector<HashtableNode<T>*> newTable(table.size() * 2, nullptr);
        
        for (int i = 0; i < table.size(); i++)
        {
            if ((table[i]) && (!table[i]->deleted))
            {
                HashtableNode<T> *node = table[i];
    
                size_t newHash = hasher(node->data) % newTable.size();
                
                for (int j = 0; j < newTable.size(); j++)
                {
                    size_t hash_try = (newHash + j) % newTable.size();
                    if (!newTable[hash_try])
                    {
                        newTable[hash_try] = node;
                        break;
                    }
                }
            }
        }
        table = move(newTable);
    }
    
    vector<HashtableNode<T>*> table;
    size_t size;
    Hasher hasher;
};

int main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    Hashtable<string, StringHasher> table;
    
    char op;
    string key;

    while (cin >> op >> key)
    {
        switch (op)
        {
            case '?':
            {
                cout << (table.Has(key) ? "OK" : "FAIL") << endl;
                break;
            }
            case '+':
            {
                cout << (table.Add(key) ? "OK" : "FAIL") << endl;
                break;
            }
            case '-':
            {
                cout << (table.Delete(key) ? "OK" : "FAIL") << endl;
                break;
            }
        }
    }
    return 0;
}