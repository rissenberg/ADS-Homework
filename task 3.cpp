/* Постройте B-дерево минимального порядка t и выведите его по слоям.
В качестве ключа используются числа, лежащие в диапазоне [0..2^32 - 1]

Требования:
B-дерево должно быть реализовано в виде шаблонного класса.
Решение должно поддерживать передачу функции сравнения снаружи.

Формат ввода
Сначала вводится минимальный порядок дерева t.
Затем вводятся элементы дерева.

Формат вывода
Программа должна вывести B-дерево по слоям.
Каждый слой на новой строке, элементы должны выводится в том порядке, в котором они лежат в узлах.
*/

// Задача является дополненным и модифицированным кодом преподавателя: добавлены функции SplitChild и BFSPrint, передача функции сравнения снаружи.

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template <typename T>
struct TreeNode
{
    TreeNode(bool flag)
    : leaf(flag)
    {
    }
    
    ~TreeNode()
    {
        for (TreeNode<T>* child: children)
        {
            delete child;
        }
    }
    
    bool leaf;
    bool last_in_line = false;
    std::vector<T> keys;
    std::vector<TreeNode<T>*> children;

};

template <typename T, typename Comparator = less<T>>
class BTree
{
public:
    BTree(size_t min_degree)
    : t(min_degree), root(nullptr)
    {
    }
    
    ~BTree()
    {
        if (root)
            delete root;
    }
    
    void Insert(const T &key)
    {
        if (!root)
        {
            root = new TreeNode<T>(true);
        }

        // здесь и дальше: если при спуске по дереву находим
        // переполненный узел -- сначала разбиваем его, потом спускаемся
        if (isNodeFull(root))
        {
            TreeNode<T> *newRoot = new TreeNode<T>(false);
            newRoot->children.push_back(root);
            root = newRoot;
            splitChild(root, 0);
        }
        
        // теперь корень точно не переполнен, можем вызвать insertNonFull
        insertNonFull(root, key);
    }
    
    void debugPrint()
    {
        debugPrintInternal(root, 0);
    }

    void BFSPrint()
    {
        queue<TreeNode<T>*> queue;
        root->last_in_line = true;
        bfsPrintInternal(root, queue);
    }
    
private:
    size_t t;
    TreeNode<T> *root;
    Comparator cmp;
    
    void debugPrintInternal(TreeNode<T> *node, int indent)
    {
        std::cout << std::string(indent, ' ');
        std::cout << "keys: [";
        for (auto it = node->keys.begin(); it != node->keys.end(); it++)
        {
            std::cout << (*it);
            if (it + 1 != node->keys.end())
                std::cout << ", ";
        }
        std::cout << "]" << std::endl;
        
        for (auto child: node->children)
        {
            debugPrintInternal(child, indent + 4);
        }
    }

    void bfsPrintInternal(TreeNode<T> *node, queue<TreeNode<T>*> queue)
    {
        if (node->leaf)
        {
            for (size_t i = 0; i < node->keys.size(); ++i)
            {
                cout << node->keys[i] << " ";
            }
            cout << endl;
            return;
        }

        TreeNode<T>* tmp = node;
        do
        {
            for (size_t i = 0; i < tmp->keys.size(); ++i)
            {
                cout << tmp->keys[i] << " ";
            }
            if (tmp->last_in_line)
            {
                cout << endl;
                if (!tmp->leaf)
                    tmp->children[tmp->children.size() - 1]->last_in_line = true;
                tmp->last_in_line = false;
            }
            if (!tmp->leaf)
                for (size_t i = 0; i < tmp->children.size(); ++i)
                {
                    queue.push(tmp->children[i]);
                }
            tmp = queue.front();
            queue.pop();
        } while (queue.size() > 0);
        
        for (size_t i = 0; i < tmp->keys.size(); ++i)
        {
            cout << tmp->keys[i] << " ";
        }
        cout << endl;

        return;
    }
    
    bool isNodeFull(TreeNode<T> *node)
    {
        return node->keys.size() == 2*t - 1;
    }
    
    // разбить переполненного потомка index узла node
    void splitChild(TreeNode<T> *node, size_t index)
    {
        TreeNode<T>* y = node->children[index];
        TreeNode<T>* z = new TreeNode<T>(y->leaf);

        for (size_t j = 0; j < t - 1; ++j) // переносим их
        {
            z->keys.push_back( y->keys[t] );
            y->keys.erase(y->keys.begin() + t);
        }
        //y->keys.resize(y->keys.size() - t + 1);

        if (!y->leaf) // если у Y есть потомки
        {
            for (size_t j = 0; j < t; ++j) // половину потомков Y
            {
                z->children.push_back( y->children[t] );// переносим в Z
                y->children.erase(y->children.begin() + t);
            }
            //y->children.resize(y->keys.size() - t);
        }

        node->children.resize(node->children.size() + 1);
        for (size_t j = node->children.size() - 2; j >= index + 1; --j)
        {
            node->children[j + 1] = node->children[j]; // сдвиг указателей на 1 вправо
        }

        node->children[index + 1] = z; // чтобы добавить указатель на Z

        node->keys.resize(node->keys.size() + 1);
        for (int i = int(node->keys.size()); i >= int(index); i--) // сдвиг ключей в X вправо
        {
            node->keys[i + 1] = node->keys[i]; // на 1 для вставки медианы
        }
        node->keys[index] = y->keys[t - 1]; // бывшего узла Y (до разбиения)
        y->keys.erase(y->keys.begin() + t - 1);
        //y->keys.resize(y->keys.size() - 1);

    }
    
    // вставить ключ key в гарантированно не переполненную ноду node
    void insertNonFull(TreeNode<T> *node, const T &key)
    {
        int pos = node->keys.size() - 1;
        
        // гарантированно не перепеполненный лист -- запишем новый ключ в него
        if (node->leaf)
        {
            // расширили вектор ключей для вставки нового
            node->keys.resize(node->keys.size() + 1);
            while (pos >= 0 && cmp(key, node->keys[pos]))
            {
                // обходим ключи справа налево, сдвигая вправо на 1
                node->keys[pos + 1] = node->keys[pos];
                pos--;
            }
            // вставляем новый ключ на освобожденное в цикле место
            node->keys[pos + 1] = key;
        }
        else
        {
            while (pos >= 0 && cmp(key, node->keys[pos]))
            {
                pos--;
            }
            
            // если потомок и так полон, надо его сначала разбить
            if (isNodeFull(node->children[pos + 1]))
            {
                splitChild(node, pos + 1);
                if (!cmp(key, node->keys[pos + 1]))
                    pos++;
            }
            insertNonFull(node->children[pos + 1], key);
        }
    }

};

int main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t;
    cin >> t;

    BTree<unsigned int, less<unsigned int>> tree(t);

    unsigned int input;
    while (cin >> input)
    {
        tree.Insert(input);
    }

    //tree.debugPrint();
    tree.BFSPrint();

    return 0;
}