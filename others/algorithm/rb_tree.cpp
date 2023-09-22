#include <iostream>
#include <assert.h>

using namespace std;

typedef enum
{
    RED = 0,
    BLACK
} Color;

// 红黑树结点类型
template <typename Type>
struct RBTNode
{
    Color color;     // 颜色
    Type key;        // 关键字
    RBTNode *left;   // 左孩子
    RBTNode *right;  // 右孩子
    RBTNode *parent; // 父结点
};

// 红黑树类型
template <typename Type>
class RBTree
{
public:
    // 构造函数
    RBTree()
    {
        Nil = BuyNode();
        root = Nil;
        Nil->color = BLACK;
    }
    // 析构函数
    ~RBTree()
    {
        destroy(root); // 销毁创建的非Nil结点
        delete Nil;    // 最后删除Nil结点
        Nil = NULL;
    }

    // 中序遍历
    void InOrder() { InOrder(root); }

    // 插入
    // 1.BST方式插入
    // 2.调整平衡
    bool Insert(const Type &value)
    {
        RBTNode<Type> *pr = Nil; // pr用来记住父节点
        RBTNode<Type> *s = root; // 定义变量s指向根
        while (s != Nil)
        {
            if (value == s->key)
            {
                return false;
            }
            pr = s; // 每次记住s的父节点
            if (value < s->key)
            {
                s = s->left;
            }
            else
            {
                s = s->right;
            }
        }
        // 循环后s==Nil
        s = BuyNode(value); // 申请结点
        if (pr == Nil)      // 如果父节点pr是根节点，第一次root指向Nil，所以pr==Nil
        {
            root = s;
            root->parent = pr;
        }
        else // 如果父节点不是根节点
        {
            if (value < pr->key)
            {
                pr->left = s;
            }
            else
            {
                pr->right = s;
            }
            s->parent = pr; // 设置新结点s的父节点
        }
        // 调整平衡
        Insert_Fixup(s);
        return true;
    }

    // 删除key结点(先查找，再调用内部删除)
    void Remove(Type key)
    {
        RBTNode<Type> *t;
        if ((t = Search(root, key)) != Nil)
        {
            Remove(t);
        }
        else
        {
            cout << "Key is not exist." << endl;
        }
    }

    // 中序遍历打印结点详细的结点颜色
    void InOrderPrint() { InOrderPrint(root); }

protected:
    // 申请结点结点，将结点的颜色初始化为红色，初始化结点的关键字，其他的初始化为空
    RBTNode<Type> *BuyNode(const Type &x = Type())
    {
        RBTNode<Type> *s = new RBTNode<Type>();
        assert(s != NULL);
        s->color = RED;
        s->left = s->right = s->parent = Nil;
        s->key = x;
        return s;
    }

    // 中序遍历
    void InOrder(RBTNode<Type> *root)
    {
        if (root != Nil)
        {
            InOrder(root->left);
            cout << root->key << " ";
            InOrder(root->right);
        }
    }

    /* 左转，对z结点左转
     *       zp                 zp
     *       /                  /
     *     z                   y
     *    / \      ===>       / \
     *   lz  y               z   ry
     *      / \             / \
     *     ly  ry          lz  ly
     */
    void LeftRotate(RBTNode<Type> *z)
    {
        RBTNode<Type> *y = z->right; // 用y指向要转动的z结点
        z->right = y->left;
        if (y->left != Nil) // y所指结点的左结点不为空
        {
            y->left->parent = z;
        }
        y->parent = z->parent;
        if (root == z) // z就是根节点
        {
            root = y;
        }
        else if (z == z->parent->left) // z在左结点
        {
            z->parent->left = y;
        }
        else // z在右结点
        {
            z->parent->right = y;
        }
        y->left = z;
        z->parent = y;
    }

    /* 右转，对z结点进行右转
     *         zp               zp
     *        /                 /
     *       z                 y
     *      / \    ===>       / \
     *     y   rz           ly   z
     *    / \                   / \
     *   ly  ry                ry  rz
     */
    void RightRotate(RBTNode<Type> *z)
    {
        RBTNode<Type> *y = z->left;
        z->left = y->right;
        if (y->right != Nil)
        {
            y->right->parent = z;
        }
        y->parent = z->parent;
        if (root == z) // 如果z是根结点
        {
            root = y;
        }
        else if (z == z->parent->left) // z在左结点
        {
            z->parent->left = y;
        }
        else // z在右结点
        {
            z->parent->right = y;
        }
        y->right = z;
        z->parent = y;
    }

    // 插入后的调整函数
    void Insert_Fixup(RBTNode<Type> *s)
    {
        RBTNode<Type> *uncle;           // 叔结点（父结点的兄弟结点）
        while (s->parent->color == RED) // 父节点的颜色也为红色
        {
            if (s->parent == s->parent->parent->left) // 父节点是左结点
            {
                uncle = s->parent->parent->right;

                if (uncle->color == RED) // 叔结点为红色
                {
                    // 父节点和叔结点都变为黑色
                    s->parent->color = BLACK;
                    uncle->color = BLACK;
                    // 祖父结点变为红色
                    s->parent->parent->color = RED;
                    // 将s指针指向祖父结点，下一次循环继续判断祖父的父节点是否为红色
                    s = s->parent->parent;
                }
                else // 没有叔结点，或叔结点为黑色(经过多次循环转换，叔结点可能为黑)
                {
                    if (s == s->parent->right) // 如果调整的结点在右结点
                    {
                        s = s->parent; // 先将s指向s的父结点
                        LeftRotate(s); // 再左转
                    }
                    // 如果调整的结点在左结点,将s的父节点变为黑色，将祖父的结点变为红色，将s的祖父结点右转
                    s->parent->color = BLACK;
                    s->parent->parent->color = RED;
                    RightRotate(s->parent->parent);
                }
            }
            else
            {
                if (s->parent == s->parent->parent->right) // 父节点是右结点
                {
                    uncle = s->parent->parent->left;
                    if (uncle->color == RED) // 叔结点为红色
                    {
                        // 父节点和叔结点都变为黑色
                        s->parent->color = BLACK;
                        uncle->color = BLACK;
                        // 祖父结点变为红色
                        s->parent->parent->color = RED;
                        // 将s指针指向祖父结点，下一次循环继续判断祖父的父节点是否为红色
                        s = s->parent->parent;
                    }
                    else // 没有叔结点，或叔结点为黑色(经过多次循环转换，叔结点可能为黑)
                    {
                        if (s == s->parent->left) // 如果调整的结点在左结点
                        {
                            s = s->parent;  // 先将s指向s的父结点
                            RightRotate(s); // 再右转
                        }
                        // 如果调整的结点在右结点,将s的父节点变为黑色，将祖父的结点变为红色，将s的祖父结点右转
                        s->parent->color = BLACK;
                        s->parent->parent->color = RED;
                        LeftRotate(s->parent->parent);
                    }
                }
            }
        }
        root->color = BLACK; // 最后始终将根节点置为黑色
    }

    // 查找key结点
    RBTNode<Type> *Search(RBTNode<Type> *root, Type key) const
    {
        if (root == Nil) // root为空，或key和根的key相同
        {
            return Nil;
        }

        if (root->key == key)
        {
            return root;
        }
        if (key < root->key)
        {
            return Search(root->left, key);
        }
        else
        {
            return Search(root->right, key);
        }
    }

    /* 将u的子节点指向u的指针改变指向v，将v的父节点指针改变为指向u的父节点
     *      up
     *        \
     *         u
     *        / \
     *      ul   ur
     *     / \
     *    v  ulr
     *     \
     *     rv
     */
    void Transplant(RBTNode<Type> *u, RBTNode<Type> *v)
    {
        if (u->parent == Nil) // u的父节点为空
        {
            root = v; // 直接令根root为v
        }
        else if (u == u->parent->left) // u父节点不为空，且u在左子树
        {
            u->parent->left = v;
        }
        else // u在右子树
        {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    /* 找到最左结点(最小)
     *      xp
     *        \
     *         x
     *        / \
     *      xl   xr
     *     / \
     *   xll  xlr
     */
    RBTNode<Type> *Minimum(RBTNode<Type> *x)
    {
        if (x->left == Nil)
        {
            return x;
        }
        return Minimum(x->left);
    }

    // 删除红黑树结点z
    void Remove(RBTNode<Type> *z)
    {
        RBTNode<Type> *x = Nil;
        RBTNode<Type> *y = z;    // y记住传进来的z结点
        Color ycolor = y->color; //
        if (z->left == Nil)      // z只有右孩子
        {
            x = z->right;
            Transplant(z, z->right);
        }
        else if (z->right == Nil) // z只有右孩子
        {
            x = z->left;
            Transplant(z, z->left);
        }
        else // 右左孩子和右孩子
        {
            y = Minimum(z->right); // y是z右子树的的最左子树
            ycolor = y->color;
            x = y->right;
            if (y->parent == z) // z的右子结点没有左节点或为Nil
            {
                x->parent = y;
            }
            else // z的右子结点有左节点或为Nil
            {
                Transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            Transplant(z, y);
            // 改变指向
            y->left = z->left;
            z->left->parent = y;
            y->color = z->color;
        }
        if (ycolor == BLACK)
        {
            Remove_Fixup(x);
        }
    }

    // 红黑树删除调整
    void Remove_Fixup(RBTNode<Type> *x)
    {
        while (x != root && x->color == BLACK) // 当结点x不为根并且它的颜色不是黑色
        {
            if (x == x->parent->left) // x在左子树
            {
                RBTNode<Type> *w = x->parent->right; // w是x的兄结点

                if (w->color == RED) // 情况1
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    LeftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) // 情况2
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->right->color == BLACK) // 情况3
                    {
                        w->color = RED;
                        w->left->color = BLACK;
                        RightRotate(w);
                        w = x->parent->right;
                    }
                    // 情况4
                    w->color = w->parent->color;
                    w->parent->color = BLACK;
                    w->right->color = BLACK;
                    LeftRotate(x->parent);
                    x = root; // 结束循环
                }
            }
            else // x在右子树
            {
                RBTNode<Type> *w = x->parent->left;
                if (w->color == RED) // 情况1
                {
                    w->parent->color = RED;
                    w->color = BLACK;
                    RightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->right->color == BLACK) // 情况2
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->left->color == BLACK) // 情况3
                    {
                        w->right->color = BLACK;
                        w->color = RED;
                        LeftRotate(w);
                        w = x->parent->left;
                    }
                    // 情况4
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    RightRotate(x->parent);
                    x = root; // 结束循环
                }
            }
        }
        x->color = BLACK;
    }

    // 销毁红黑树
    void destroy(RBTNode<Type> *&root)
    {
        if (root == Nil)
        {
            return;
        }
        if (root->left != Nil)
        {
            destroy(root->left);
        }
        if (root->right != Nil)
        {
            destroy(root->right);
        }
        delete root;
        root = NULL;
    }

    // 中序遍历打印结点详细的结点颜色
    void InOrderPrint(RBTNode<Type> *node)
    {
        if (node == Nil)
        {
            return;
        }
        if (node->left != NULL)
        {
            InOrderPrint(node->left);
        }
        cout << node->key << "(" << ((node->color == BLACK) ? "BLACK" : "RED") << ")"
             << " ";
        if (node->right != Nil)
        {
            InOrderPrint(node->right);
        }
    }

private:
    RBTNode<Type> *root; // 根指针
    RBTNode<Type> *Nil;  // 外部结点，表示空结点，黑色的
};

int main(int argc, char *argv[])
{
    RBTree<int> rb;

    int arr[] = {10, 7, 8, 15, 5, 6, 11, 13, 12};
    int n = sizeof(arr) / sizeof(int);
    for (int i = 0; i < n; i++)
    {
        rb.Insert(arr[i]);
    }

    rb.InOrder();
    cout << endl;
    rb.InOrderPrint();
    cout << endl;
    rb.Remove(10);
    rb.InOrder();
    cout << endl;
    rb.Remove(21);
    return 0;
}
