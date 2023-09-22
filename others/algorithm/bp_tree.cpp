template <typename T>
class Node
{
    T key;
    Node *left;
    Node *right;
    bool isLeaf;
    Node *parent;

    Node(T key, Node *left, Node *right, bool isLeaf, Node *parent)
    {
        this->key = key;
        this->left = left;
        this->right = right;
        this->isLeaf = isLeaf;
        this->parent = parent;
    }
};

template <typename T>
class BTree
{
    Node<T> *root;
    int m; // 阶数

public:
    BTree(int m)
    {
        root = nullptr;
        this->m = m;
    }

    // 查找关键字key所在的节点
    Node<T> *search(T key)
    {
        Node<T> *cur = root;
        while (cur != nullptr)
        {
            if (key == cur->key)
                return cur;
            else if (key < cur->key)
                cur = cur->left;
            else
                cur = cur->right;
        }
        return nullptr;
    }

    // 向树中插入关键字key
    void insert(T key)
    {
        // 找到父节点parent和叶子节点leaf
        Node<T> *leaf = search(key);
        Node<T> *parent = nullptr;
        if (leaf == nullptr)
        { // 没找到,树为空,插入根节点
            root = new Node<T>(key, nullptr, nullptr, true, nullptr);
            return;
        }
        else
        {
            parent = leaf->parent;
        }

        if (leaf->isLeaf)
        { // 找到叶子节点,插入
            if (key == leaf->key)
                return; // key已存在,不插入
            else if (key < leaf->key)
            {
                leaf->left = new Node<T>(key, nullptr, nullptr, true, leaf);
                leaf->left->parent = leaf;
            }
            else
            {
                leaf->right = new Node<T>(key, nullptr, nullptr, true, leaf);
                leaf->right->parent = leaf;
            }
        }
        else
        { // 未找到叶子,继续递归插入
            if (key < leaf->key)
                insert(key, leaf->left);
            else
                insert(key, leaf->right);
        }

        // 插入后,检测阶数是否超过m,若超过则拆分
        if (leaf->isLeaf && (leaf->left != nullptr && leaf->left->isLeaf) && (leaf->right != nullptr && leaf->right->isLeaf) && (leaf->left->key - leaf->key) + (leaf->key - leaf->right->key) > m)
        {
            split(leaf);
        }
    }

private:
    // 拆分节点,节点分裂成两个节点
    void split(Node<T> *node)
    {
        // 找到中位数key和中点midpoint
        T midKey;
        Node<T> *midNode;
        if (node->left->isLeaf && node->right->isLeaf)
        {
            midKey = (node->left->key + node->key) / 2;
            midNode = node->left;
        }
        else if (node->left->isLeaf)
        {
            midKey = node->left->key;
            midNode = node->left;
        }
        else if (node->right->isLeaf)
        {
            midKey = node->key;
            midNode = node;
        }

        // 创建新节点newNode,并移动节点至newNode
        Node<T> *newNode = new Node<T>(midKey, nullptr, nullptr, true, node->parent);
        if (midNode == node)
        { // 以node节点中间键为分界
            newNode->left = node->left;
            node->left->parent = newNode;
            node->left = midNode->right;
            midNode->right->parent = node;
            newNode->right = midNode->right;
            midNode->right = nullptr;
        }
        else
        { // 以node左子节点或右子节点为分界
            newNode->left = midNode->left;
            newNode->right = node->right;
            node->right = nullptr;
            midNode->left = nullptr;
        }
    }
};

template <typename T>
class BPlusTree
{
    Node<T> *root;
    int m; // 阶数

public:
    BPlusTree(int m)
    {
        root = nullptr;
        this->m = m;
    }

    // 查找关键字key所在的节点
    Node<T> *search(T key)
    {
        Node<T> *cur = root;
        while (cur != nullptr && !cur->isLeaf)
        {
            cur = key < cur->key ? cur->next : cur->pre;
        }
        return cur;
    }

    // 向树中插入关键字key
    void insert(T key)
    {
        Node<T> *leaf = search(key);
        if (leaf == nullptr)
        { // 树为空,插入根节点
            root = new Node<T>(key, nullptr, nullptr, true, nullptr);
            return;
        }

        if (key == leaf->key)
            return; // key已存在,不插入

        // 找到叶子节点后插入
        Node<T> *newNode = new Node<T>(key, nullptr, nullptr, true, leaf->parent);
        if (key < leaf->key)
        { // 插入到当前节点之前
            newNode->next = leaf;
            newNode->pre = leaf->pre;
            leaf->pre->next = newNode;
            leaf->pre = newNode;
        }
        else
        { // 插入到当前节点之后
            newNode->pre = leaf;
            newNode->next = leaf->next;
            leaf->next->pre = newNode;
            leaf->next = newNode;
        }

        // 插入后,检测阶数是否超过m,若超过则拆分
        if (leaf != nullptr && leaf->next != nullptr && leaf->pre != nullptr && leaf->next->key - leaf->key + leaf->key - leaf->pre->key > m)
        {
            split(leaf);
        }
    }

private:
    // 拆分节点,节点分裂成两个节点
    void split(Node<T> *node)
    {
        Node<T> *newNode;
        T midKey;

        if (node == root)
        { // 根节点拆分
            midKey = (node->next->key + node->key) / 2;
            newNode = new Node<T>(midKey, node->next, node, false, nullptr);
            node->next->pre = newNode;
            node->next = newNode->next;
            node->next->pre = node;
            newNode->next = node;
            root = newNode;
            return;
        }

        if (node->pre->key < node->key && node->key < node->next->key)
        {
            midKey = (node->pre->key + node->key) / 2;
            newNode = new Node<T>(midKey, node->pre->next, node->pre, false, node->parent);
            node->pre->next = newNode;
            node->pre = newNode;
        }
        else if (node->key < node->next->key && node->next->key < node->pre->key)
        {
            midKey = (node->key + node->next->key) / 2;
            newNode = new Node<T>(midKey, node, node->next, false, node->parent);
            node->next->pre = newNode;
            node->next = newNode->next;
            node->next->pre = node;
            newNode->next = node->next;
        }
    }
};
