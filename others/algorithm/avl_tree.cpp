#pragma once
using namespace std;
#include <iostream>
#include <queue>
template <class K, class V>
struct AVLTreeNode
{
    AVLTreeNode(const pair<K, V> &kv = pair<K, V>())
        : _left(nullptr), _right(nullptr), _parent(nullptr), _bf(0), _kv(kv)
    {
    }
    AVLTreeNode<K, V> *_left;
    AVLTreeNode<K, V> *_right;
    AVLTreeNode<K, V> *_parent;

    int _bf; // balance factor 平衡因子

    pair<K, V> _kv;
};

template <class K, class V>
class AVLTree
{
public:
    typedef struct AVLTreeNode<K, V> Node;
    // 右单旋
    void RotateR(Node *parent)
    {
        Node *cur = parent->_left;
        Node *curR = cur->_right;        // cur的右子树
        Node *pparent = parent->_parent; // 保存parent的父亲节点

        // 将cur右子树链接到parent的左侧
        parent->_left = curR;
        if (curR)
            curR->_parent = parent;

        // 将parent连接到cur的右侧
        cur->_right = parent;
        parent->_parent = cur;

        // 将cur与pparent链接起来
        if (pparent == nullptr) // cur变成新的根
        {
            _root = cur;
            cur->_parent = nullptr;
        }
        else // pparent不为根
        {
            cur->_parent = pparent;
            if (parent == pparent->_left) // parent在父亲节点的左侧
            {
                pparent->_left = cur;
            }
            else
            {
                pparent->_right = cur;
            }
        }

        // 平衡因子更新
        parent->_bf = 0;
        cur->_bf = 0;
    }
    // 左单旋
    void RotateL(Node *parent) // 左旋
    {
        Node *cur = parent->_right; // 右变高，不可能为空
        Node *curL = cur->_left;
        Node *pprent = parent->_parent;

        // curL连接到parent上
        parent->_right = curL;
        if (curL)
            curL->_parent = parent;

        // parent连接到cur上
        cur->_left = parent;
        parent->_parent = cur;

        // cur链接到pprent上
        if (pprent == nullptr) // 根
        {
            _root = cur;
            cur->_parent = nullptr;
        }
        else // 不为根
        {
            cur->_parent = pprent;
            // 判断链接在哪一侧
            if (pprent->_left == parent)
            {
                pprent->_left = cur;
            }
            else
            {
                pprent->_right = cur;
            }
        }

        // 平衡因子的更新
        parent->_bf = 0;
        cur->_bf = 0;
    }

    // 左右双旋
    void RotateLR(Node *parent)
    {
        Node *cur = parent->_left;
        Node *curR = cur->_right; // 此时不可能为空，因为右子树高

        int bf = curR->_bf; // 保存一份平衡因子

        RotateL(cur);    // 先左旋
        RotateR(parent); // 再右旋

        // 左旋、右旋会将平衡因子全部处理成0，因此要对平衡因子进行更改

        if (bf == 1) // 在curR的右侧插入
        {
            curR->_bf = 0;
            cur->_bf = -1;
            parent->_bf = 0;
        }
        else if (bf == -1) // 在curR左侧插入
        {
            curR->_bf = 0;
            cur->_bf = 0;
            parent->_bf = 1;
        }
    }
    // 右左双旋
    void RotateRL(Node *parent)
    {
        Node *cur = parent->_right;
        Node *curL = cur->_left;

        int bf = curL->_bf;

        RotateR(cur);    // 先右旋
        RotateL(parent); // 再左旋

        // 平衡因子出来

        if (bf == 1) // 在subRL右侧插入时
        {
            curL->_bf = 0;
            parent->_bf = -1;
            cur->_bf = 0;
        }
        else if (bf == -1) // 在左侧插入时
        {
            curL->_bf = 0;
            parent->_bf = 0;
            cur->_bf = 1;
        }
    }
    bool Insert(const pair<K, V> &kv)
    {
        if (_root == nullptr)
        {
            _root = new Node(kv);
            return true;
        }

        // 有根了，按照平衡二叉树的方法进行插入
        Node *parent = nullptr;
        Node *cur = _root;
        while (cur)
        {
            if (kv.first < cur->_kv.first) // K值比较，小于往左边走
            {
                parent = cur;
                cur = cur->_left;
            }
            else if (kv.first > cur->_kv.first) // 往右走
            {
                parent = cur;
                cur = cur->_right;
            }
            else // 相等，不进行插入
            {
                return false;
            }
        }

        // 此时已经找到插入的位置了,判断插入在parent的左边还是右边
        cur = new Node(kv);
        if (parent->_kv.first > kv.first) // 插在左边
        {
            parent->_left = cur;
            cur->_parent = parent; // 三叉链，cur父指针回指
        }
        else // 插在右边
        {
            parent->_right = cur;
            cur->_parent = parent; // 三叉链，cur父指针回指
        }

        // 更新平衡因子
        while (parent) // 不为空
        {
            if (parent->_left == cur) // cur在parent左侧
            {
                parent->_bf--;
            }
            else // cur在parent右侧
            {
                parent->_bf++;
            }

            if (parent->_bf == 0) // 当前树是平衡的，停止更新
                break;
            else if (parent->_bf == 1 || parent->_bf == -1) // 继续往上面走
            {
                cur = parent;
                parent = parent->_parent;
            }
            else if (parent->_bf == 2 || parent->_bf == -2) // 需要进行旋转处理
            {
                if (parent->_bf == -2) // 左边高
                {
                    if (cur->_bf == -1) // 是在当前节点的左侧插入了节点 ->右单旋
                    {
                        RotateR(parent);
                    }
                    else // cur->_bf=1 ->曲线影响,需要进行左右双旋
                    {
                        RotateLR(parent);
                    }
                }
                else // 右边高
                {
                    if (cur->_bf == 1) // 在当前节点的右侧插入了节点 ->  左单旋
                    {
                        RotateL(parent);
                    }
                    else // cur->_bf=-1 曲线影响
                    {
                        RotateRL(parent);
                    }
                }
                break; // 旋转过后当前的树就是平衡的了，退出
            }
            else // 0 1 2 -> 不可能走到这一步，走到这里说明发生了逻辑错误
            {
                exit(-1);
            }
        }
        return true;
    }

    // 删除函数
    bool Erase(const K &key)
    {
        // 用于遍历二叉树
        Node *parent = nullptr;
        Node *cur = _root;
        // 用于标记实际的删除结点及其父结点
        Node *delParentPos = nullptr;
        Node *delPos = nullptr;
        while (cur)
        {
            if (key < cur->_kv.first) // 所给key值小于当前结点的key值
            {
                // 往该结点的左子树走
                parent = cur;
                cur = cur->_left;
            }
            if (key > cur->_kv.first) // 所给key值小于当前结点的key值
            {
                // 往该结点的右子树走
                parent = cur;
                cur = cur->_right;
            }
            else // 找到了待删除结点
            {
                if (cur->_left == nullptr) // 待删除结点的左子树为空
                {
                    if (cur == _root) // 待删除结点是根结点
                    {
                        _root = _root->_right; // 让根结点的右子树作为新的根结点
                        // 如果此时_root为空，此时寻找去父亲指针会对空指针解引用而报错，因此需要判断
                        if (_root)
                            _root->_parent = nullptr;
                        delete cur;  // 删除原根结点
                        return true; // 根结点无祖先结点，无需进行平衡因子的更新操作
                    }
                    else
                    {
                        delParentPos = parent; // 标记实际删除结点的父结点
                        delPos = cur;          // 标记实际删除的结点
                    }
                    break; // 删除结点有祖先结点，需更新平衡因子
                }
                else if (cur->_right == nullptr) // 待删除结点的右子树为空
                {
                    if (cur == _root) // 待删除结点是根结点
                    {
                        _root = _root->_left; // 让根结点的左子树作为新的根结点
                        // 如果此时_root为空，此时寻找去父亲指针会对空指针解引用而报错，因此需要判断
                        if (_root)
                            _root->_parent = nullptr;
                        delete cur;  // 删除原根结点
                        return true; // 根结点无祖先结点，无需进行平衡因子的更新操作
                    }
                    else
                    {
                        delParentPos = parent; // 标记实际删除结点的父结点
                        delPos = cur;          // 标记实际删除的结点
                    }
                    break; // 删除结点有祖先结点，需更新平衡因子
                }
                else // 待删除结点的左右子树均不为空
                {
                    // 替换法删除
                    // 寻找待删除结点右子树当中key值最小的结点作为实际删除结点
                    Node *minParent = cur;
                    Node *minRight = cur->_right;
                    while (minRight->_left)
                    {
                        minParent = minRight;
                        minRight = minRight->_left;
                    }
                    cur->_kv.first = minRight->_kv.first;   // 将待删除结点的key改为minRight的key
                    cur->_kv.second = minRight->_kv.second; // 将待删除结点的value改为minRight的value
                    delParentPos = minParent;               // 标记实际删除结点的父结点
                    delPos = minRight;                      // 标记实际删除的结点
                    break;                                  // 删除结点有祖先结点，需更新平衡因子
                }
            }
        }
        if (delParentPos == nullptr) // delParentPos没有被修改过，说明没有找到待删除结点
        {
            return false;
        }

        // 记录待删除结点及其父结点
        Node *del = delPos;
        Node *delP = delParentPos;

        // 更新平衡因子
        while (delPos != _root)
        {
            // 判断删除的是在父亲的哪一边，然后更新平衡因子
            if (delPos == delParentPos->_left)
            {
                delParentPos->_bf++;
            }
            else if (delPos == delParentPos->_right)
            {
                delParentPos->_bf--;
            }
            // 当前树是平衡的，停止更新
            if (delParentPos->_bf == -1 || delParentPos->_bf == 1)
            {
                break; // delParent树的高度没有发生变化，不会影响其父结点及以上结点的平衡因子
            }
            else if (delParentPos->_bf == 0) // 需要继续往上更新平衡因子
            {
                // delParentPos树的高度变化，会影响其父结点的平衡因子，需要继续往上更新平衡因子
                delPos = delParentPos;
                delParentPos = delParentPos->_parent;
            }

            else if (delParentPos->_bf == -2 || delParentPos->_bf == 2) // 需要进行旋转处理
            {
                if (delParentPos->_bf == -2) // 左边高
                {
                    if (delParentPos->_left->_bf == -1) // 左边高，进行右单旋
                    {
                        Node *tmp = delParentPos->_left; // 记录delParentPos右旋转后新的根结点
                        RotateR(delParentPos);           // 右单旋
                        delParentPos = tmp;              // 更新根结点
                    }
                    else if (delParentPos->_left->_bf == 1) // 曲线影响,需要进行左右双旋
                    {
                        Node *tmp = delParentPos->_left->_right; // 记录delParentPos左右旋转后新的根结点
                        RotateLR(delParentPos);                  // 左右双旋
                        delParentPos = tmp;                      // 更新根结点
                    }
                    else // delParentPos->_left->_bf == 0
                    {
                        Node *tmp = delParentPos->_left; // 记录delParentPos右旋转后新的根结点
                        RotateR(delParentPos);           // 右单旋
                        delParentPos = tmp;              // 更新根结点
                        // 平衡因子调整
                        delParentPos->_bf = 1;
                        delParentPos->_right->_bf = -1;
                        break;
                    }
                }
                else // delParentPos->_bf == 2
                {
                    if (delParentPos->_right->_bf == -1)
                    {
                        Node *tmp = delParentPos->_right->_left; // 记录delParentPos右左旋转后新的根结点
                        RotateRL(delParentPos);                  // 右左双旋
                        delParentPos = tmp;                      // 更新根结点
                    }
                    else if (delParentPos->_right->_bf == 1) // 曲线影响,需要进行左右双旋
                    {
                        Node *tmp = delParentPos->_right; // 记录delParentPos左旋转后新的根结点
                        RotateL(delParentPos);            // 左单旋
                        delParentPos = tmp;               // 更新根结点
                    }
                    else // delParentPos->_right->_bf == 0
                    {
                        Node *tmp = delParentPos->_right; // 记录delParentPos左旋转后新的根结点
                        RotateL(delParentPos);            // 左单旋
                        delParentPos = tmp;               // 更新根结点
                        // 平衡因子调整
                        delParentPos->_bf = -1;
                        delParentPos->_left->_bf = 1;
                        break;
                    }
                }
                // 继续往上更新平衡因子
                delPos = delParentPos;
                delParentPos = delParentPos->_parent;
            }
            else
            {
                exit(-1); // 不会到这里，到这里说明出现了错误
            }
        }
        // 进行实际删除
        if (del->_left == nullptr) // 实际删除结点的左子树为空
        {
            if (del == delP->_left) // 实际删除结点是其父结点的左孩子
            {
                delP->_left = del->_right;
                if (del->_right)
                    del->_right->_parent = parent;
            }
            else // 实际删除结点是其父结点的右孩子
            {
                delP->_right = del->_right;
                if (del->_right)
                    del->_right->_parent = parent;
            }
        }
        else // 实际删除结点的右子树为空
        {
            if (del == delP->_left) // 实际删除结点是其父结点的左孩子
            {
                delP->_left = del->_left;
                if (del->_left)
                    del->_left->_parent = parent;
            }
            else // 实际删除结点是其父结点的右孩子
            {
                delP->_right = del->_left;
                if (del->_left)
                    del->_left->_parent = parent;
            }
        }
        delete del; // 实际删除结点
        return true;
    }

    // 遍历的时候 root为private外面无法拿到
    // 因此需要封装一层
    void _Inorder(Node *root)
    {
        if (root == nullptr)
            return;
        _Inorder(root->_left);
        cout << root->_kv.first << " " << root->_kv.second << endl;
        _Inorder(root->_right);
    }
    // 中序遍历
    void Inorder()
    {
        _Inorder(_root);
    }

    Node *Find(const K &k)
    {
        Node *cur = _root;
        while (cur)
        {
            if (cur->_kv.first > k)
                cur = cur->_left;
            else if (cur->_kv.first < k)
                cur = cur->_right;
            else
                return cur;
        }
        return false;
    }

    // 求树的深度
    int maxDepth(Node *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        int leftDepth = maxDepth(root->_left);
        int rightDepth = maxDepth(root->_right);
        return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
    }
    bool _isBalanced(Node *root)
    {
        if (root == nullptr)
        {
            return true;
        }
        int leftHight = maxDepth(root->_left);
        int rightHight = maxDepth(root->_right);
        return abs(leftHight - rightHight) < 2 && _isBalanced(root->_left) && _isBalanced(root->_right);
    }
    bool isBalanced()
    {
        return _isBalanced(_root);
    }

private:
    Node *_root = nullptr;
};