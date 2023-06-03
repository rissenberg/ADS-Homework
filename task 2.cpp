/* Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.
2_2. Выведите элементы в порядке pre-order (сверху вниз).
*/

#include <iostream>
#include <stack>

using namespace std;

template <typename T>
struct TreeNode
{
    TreeNode()
    {
    }
    
    TreeNode(const T &data)
    : data(data), Left(nullptr), Right(nullptr)
    {
    }

    ~TreeNode()
    {
    }
    
    T data;
    TreeNode<T>* Right;
    TreeNode<T>* Left;

};

template <typename T, typename Comparator = less<T>>
class BinaryTree
{
public:
    BinaryTree()
    : root(nullptr)
    {
    }
    
    ~BinaryTree()
    {
        destroyTree(root);
    }

    void Add(const T &data)
    {
        root = addInternal(root, data);
    }

    void PreOrderPrint()
    {
        stack<TreeNode<T>*> stack;
        TreeNode<T>* tmp = root;
        while (true)
        {
            cout << tmp->data << " ";
            if (tmp->Right)
                stack.push(tmp->Right);
            if ((!tmp->Left) && (stack.empty()))
                return;
            if (!tmp->Left)
            {
                tmp = stack.top();
                stack.pop();
            }
                
            else
                tmp = tmp->Left;
        }
    }

private:
    TreeNode<T>* root;
    Comparator cmp;

    void destroyTree(TreeNode<T> *node)
    {
        if (node)
        {
            stack<TreeNode<T>*> stack;
            stack.push(node);
            while (!stack.empty())
            {
                if (node->Right)
                    stack.push(Right);
                if (node->Left)
                    stack.push(Left);
                delete node;
            }
        }
    }

    TreeNode<T>* addInternal(TreeNode<T> *node, const T &data)
    {
        if (!node)
            return new TreeNode<T>(data);
        if (cmp(node->data, data))
            node->Right = addInternal(node->Right, data);
        else
            node->Left = addInternal(node->Left, data);

        return node;
    }

};

int main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    BinaryTree<int, less<int>> tree; 
    int n;
    int input;

    cin >> n;

    for (int i = 0; i < n; i++) 
    {
        cin >> input;
        tree.Add(input);
    }

    tree.PreOrderPrint();

    return 0;
}
