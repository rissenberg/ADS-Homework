/* 4_1. Солдаты. В одной военной части решили построить в одну шеренгу 
по росту. Т.к. часть была далеко не образцовая, то солдаты часто 
приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги 
за плохо начищенные сапоги. Однако солдаты в процессе прихода и ухода 
должны были всегда быть выстроены по росту – сначала самые высокие, 
а в конце – самые низкие. За расстановку солдат отвечал прапорщик, 
который заметил интересную особенность – все солдаты в части разного 
роста. Ваша задача состоит в том, чтобы помочь прапорщику правильно 
расставлять солдат, а именно для каждого приходящего солдата указывать, 
перед каким солдатом в строе он должен становится. 
Требования: скорость выполнения команды - O(log n).
*/

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
struct TreeNode
{
    TreeNode()
    {
    }
    
    TreeNode(const T &data)
    : data(data), Left(nullptr), Right(nullptr), height(1), count (1)
    {
    }

    ~TreeNode()
    {
    }
    
    T data;
    TreeNode<T>* Right;
    TreeNode<T>* Left;
    size_t height;
    size_t count;
};

template <typename T, typename Comparator = less<T>>
class AVLTree
{
public:
    AVLTree()
    : root(nullptr)
    {
    }
    
    ~AVLTree()
    {
        destroyTree(root);
    }
    
    void Add(const T &data)
    {
        root = addInternal(root, data);
    }

    int AddAndGetIndex(const T &data)
    {
        root = addInternal(root, data);
        return indexOfNode(data);
    }

    int GetIndex(const T &data)
    {
        return indexOfNode(data);
    }

    T GetValue(int index)
    {
        return nodeByIndex(index);
    }

    bool Exists(const T &data)
    {
        TreeNode<T> *tmp = root;
        while (tmp)
        {
            if (tmp->data == data)
                return true;
            else if (cmp(tmp->data, data))
                tmp = tmp->Right;
            else
                tmp = tmp->Left;
        }
        return false;
    }

    void Delete(const T &data)
    {
        root = deleteInternal(root, data);
    }

    void DeleteByIndex(const int &index)
    {
        T data = nodeByIndex(index);
        root = deleteInternal(root, data);
    }

private:
    TreeNode<T>* root;
    Comparator cmp = Comparator();

    void destroyTree(TreeNode<T> *node)
    {
        if (node)
        {
            destroyTree(node->Left);
            destroyTree(node->Right);
            delete node;
        }
    }

    int indexOfNode(const T &data)
    {
        TreeNode<T> *tmp = root;
        int counter = 0;
        while (tmp)
        {
            if (cmp(data, tmp->data))
            {
                tmp = tmp->Left; 
            }
            else
            {
                if (tmp->data == data)
                {
                    counter += getCount(tmp->Left);
                    return counter;
                }
                counter += getCount(tmp->Left) + 1;
                tmp = tmp->Right;
            }
        }
        return -1;
    }

    T nodeByIndex(int index)
    {
        TreeNode<T> *tmp = root;
        index++;
        while (tmp)
        {
            if (getCount(tmp->Left) >= index)  
            {
                if (tmp->count - getCount(tmp->Right) == index)
                    return tmp->data;
                tmp = tmp->Left;
            }   
            else
            {
                if (tmp->count - getCount(tmp->Right) == index)
                    return tmp->data;
                index = index - getCount(tmp->Left) - 1;
                tmp = tmp->Right;
            }
        }
        return 0;
    }

    TreeNode<T>* findMin(TreeNode<T> *node)
    {
        while (node->Left)
            node = node->Left;
        return node;
    }
    
    TreeNode<T>* removeMin(TreeNode<T> *node)
    {
        if (!node->Left)
            return node->Right;
        node->Left = removeMin(node->Left);
        return doBalance(node);
    }

    TreeNode<T>* deleteInternal(TreeNode<T> *node, const T &data)
    {
        if (!node)
        {
            return nullptr;
        }
        if (cmp(node->data, data))
        {
            node->Right = deleteInternal(node->Right, data);
        }
        else if (cmp(data, node->data))
            node->Left = deleteInternal(node->Left, data);
        else
        {
            TreeNode<T> *left = node->Left;
            TreeNode<T> *right = node->Right;
            
            delete node;
            
            if (!right)
            {
                return left;
            }
    
            TreeNode<T> *min = findMin(right); 
            min->Right = removeMin(right);
            min->Left = left;
            
            return doBalance(min);
        }
        
        return doBalance(node);
    }

    TreeNode<T>* addInternal(TreeNode<T> *node, const T &data)
    {
        if (!node)
            return new TreeNode<T>(data);
        if (!cmp(data, node->data))
            node->Right = addInternal(node->Right, data);
        else
            node->Left = addInternal(node->Left, data);
        
        return doBalance(node);
    }

    size_t getHeight(TreeNode<T> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return node->height;
    }

    size_t getCount(TreeNode<T> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return node->count;
    }
    
    void fixHeight(TreeNode<T> *node)
    {
        node->height = std::max(getHeight(node->Left), getHeight(node->Right)) + 1;
    }

    void fixCount(TreeNode<T> *node)
    {
        node->count = getCount(node->Left) + getCount(node->Right) + 1;
    }
    
    int getBalance(TreeNode<T> *node)
    {
        return getHeight(node->Right) - getHeight(node->Left);
    }
    
    TreeNode<T>* rotateLeft(TreeNode<T> *node)
    {
        TreeNode<T> *tmp = node->Right;
        node->Right = tmp->Left;
        tmp->Left = node;
        fixHeight(node);
        fixHeight(tmp);
        fixCount(node);
        fixCount(tmp);
        return tmp;
    }
    
    TreeNode<T>* rotateRight(TreeNode<T> *node)
    {
        TreeNode<T> *tmp = node->Left;
        node->Left = tmp->Right;
        tmp->Right = node;
        fixHeight(node);
        fixHeight(tmp);
        fixCount(node);
        fixCount(tmp);
        return tmp;
    }

    TreeNode<T>* doBalance(TreeNode<T> *node)
    {
        fixHeight(node);
        fixCount(node);
        switch (getBalance(node))
        {
            case 2:
            {
                if (getBalance(node->Right) < 0)
                    node->Right = rotateRight(node->Right);
                return rotateLeft(node);
            }
            case -2:
            {
                if (getBalance(node->Left) > 0)
                    node->Left = rotateLeft(node->Left);
                return rotateRight(node);
            }
            default:
                return node;
        }
    }
};

int main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    AVLTree<int, greater<int>> tree; 
    int n;
    short int command;
    int input;

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> command >> input;

        if (command == 1) 
            cout << tree.AddAndGetIndex(input) << '\n';
        else
        {
            tree.DeleteByIndex(input);
        }
    }

    return 0;
}

/* 	В программе реализована k-порядковая статистика для поиска по индексам узлов и индексов по значениям узла.
	Сложность работы алгоритма добавления и возврата индекса: T(n) = O((log n + 1) + log n) = O(2log n) = O(log n);
    Сложность работы алгоритма удаления по индексу: T(n) = O(log n + (log n + 1)) = O(log n);  */