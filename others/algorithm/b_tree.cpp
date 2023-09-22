/*
项目名：B-树
作者：龙卡
完成时间：2020/12/21 0:04
个人感受：手撕B-树真的太难了，要想写好还得在每一步把所有可能的情况全部考虑完，调试过程中遇到的最严重的bug就是par指针
的维护不到位，有很多情况没有维护好，导致出了bug。
*/
#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;
const int M = 5;                          // B-树的阶
const int MAX_N = M - 1;                  // 关键字个数最大值
const int MIN_N = (M >> 1) + (M & 1) - 1; // 最小值
const int SIZE = M + 1;                   // key，pchild的真实容量，+1是为了处理插入的情况
const int MID = (M >> 1) + (M & 1);       // m/2向上取整

template <typename T>
class BMTree;
template <typename T>
class result;

// #define private public//debug永远滴神

template <class T>
class node
{
private:
    int n; // 关键字的个数
    T key[SIZE];
    node<T> *pchild[SIZE];
    node<T> *par;
    node(int n, node<T> *par = NULL) : n(n), par(par)
    {
        for (int i = 0; i < SIZE; i++)
            pchild[i] = NULL;
    }                              // 我真没有压行的嫌疑[捂脸]
    int insert_key(const T &value) // 在key中插入value,返回插入的位置下标
    {
        int pos = upper_bound(key + 1, key + n + 1, value) - key;
        for (int i = ++n; i > pos; i--)
            key[i] = key[i - 1], pchild[i] = pchild[i - 1];
        key[pos] = value;
        return pos;
    }
    void delete_key(int pos)
    {
        if (pos < 0 || pos > n)
            throw "delete_key Error:Index out of range.";
        for (int i = pos; i <= n; i++)
            key[i] = key[i + 1], pchild[i] = pchild[i + 1]; // 这里小于等于n是为了让没用的指针保持为空,避免插入时候的隐患
        n--;
    }
    node<T> *split() // 自己作为左儿子分裂，返回分裂后的右儿子指针
    {
        node<T> *lchild = this, *rchild = new node(M / 2, this->par);
        this->n = MID - 1;
        for (int i = MID + 1; i <= M; i++)
            rchild->key[i - MID] = lchild->key[i];
        for (int i = MID; i <= M; i++)
            rchild->pchild[i - MID] = lchild->pchild[i];
        return rchild;
    }
    bool too_big() const { return n > MAX_N; }
    bool rich() const { return n > MIN_N; } // 大于最小值说明可以删掉一个，就比较富有的啦
    bool too_small() const { return n < MIN_N; }
    static node<T> *merge(node<T> *a, node<T> *b, const T &value) // 左a右b，顺序很要紧
    {
        a->key[++(a->n)] = value;
        a->pchild[a->n] = b->pchild[0];
        for (int i = 1; i <= b->n; i++)
            a->key[i + a->n] = b->key[i], a->pchild[i + a->n] = b->pchild[i];
        a->n += b->n;
        delete b;
        return a;
    }
    friend class BMTree<T>;
    friend class result<T>;
};

template <typename T>
class result
{
public:
    bool tag;
    int i;
    node<T> *p;
    deque<int> path;
    result() {}
    result(node<T> *p, int i, bool tag, const deque<int> &path) : p(p), i(i), tag(tag), path(path) {}
    void show()
    {
        cout << "R";
        for (deque<int>::iterator ite = path.begin(); ite != path.end(); ++ite)
            cout << *ite;
        cout << ",n=" << p->n << "(";
        for (int i = 1; i <= p->n; i++)
            cout << "," + !(i - 1) << p->key[i];
        cout << ")\n";
    }
};

template <typename T>
class BMTree
{
private:
    node<T> *head;

private:
    BMTree(BMTree &b) {}

public:
    BMTree() : head(NULL) {}
    ~BMTree() { clear(head); } // 删除树中的所有结点
private:
    void refresh(node<T> *ptr)
    {
        for (int i = 0; i <= ptr->n && ptr->pchild[i]; i++)
            ptr->pchild[i]->par = ptr;
    }
    void clear(node<T> *ptr)
    {
        if (!ptr)
            return;
        for (int i = 0; i <= ptr->n; i++)
            clear(ptr->pchild[i]);
        delete ptr;
    }
    void split(node<T> *ptr) // 从p结点开始分裂
    {
        if (ptr->n <= MAX_N)
            return; // 没有超过需求
        node<T> *par = ptr->par;
        int i = 1;
        if (!par) // 没有父亲结点，说明当前是头节点
        {
            par = new node<T>(1);
            head = par;
            ptr->par = par;
            par->key[1] = ptr->key[MID];
        }
        else
            i = ptr->par->insert_key(ptr->key[MID]);
        node<T> *rchild = ptr->split(), *lchild = ptr;
        par->pchild[i - 1] = lchild;
        par->pchild[i] = rchild;
        refresh(rchild); // 就这个bug可以de一天
        split(ptr->par);
    }
    void check(node<T> *ptr, node<T> *last = NULL) // debug用的，不必在意
    {
        if (!ptr)
            return;
        if (ptr->par != last)
            cout << "Error 错误结点对应的首个关键字" << ptr->key[1] << '\n';
        for (int i = 0; i <= ptr->n; i++)
            check(ptr->pchild[i], ptr);
    }
    void merge(node<T> *ptr)
    {
        check(head);
        if (ptr->n >= MIN_N)
            return;
        if (ptr == head)
        {
            if (ptr->n > 0)
                return;  // 头节点指针个数可以少于MIN_N;
            delete head; // 结点被全部删除完了
            head = NULL;
            return;
        }
        node<T> *par = ptr->par, *rbro = NULL, *lbro = NULL;
        T *key = par->key;
        int i = upper_bound(key + 1, key + par->n + 1, ptr->key[1]) - key - 1;
        if (i > 0)
            lbro = par->pchild[i - 1];
        if (i < par->n)
            rbro = par->pchild[i + 1];
        // 这下面的很多父亲结点没有改变，导致错误（已被修复，不愧是我，✌( •`ω •^ )✌）
        if (lbro && lbro->rich())
        {
            ptr->insert_key(par->key[i]);
            ptr->pchild[1] = ptr->pchild[0];
            ptr->pchild[0] = lbro->pchild[lbro->n], par->key[i] = lbro->key[lbro->n]; // 将左兄弟的最大值提上去
            // 删除再插入可能会有指针问题，记得清空指针
            lbro->delete_key(lbro->n);
            refresh(ptr);
            return;
        }
        if (rbro && rbro->rich())
        {
            ptr->insert_key(par->key[i + 1]);
            ptr->pchild[ptr->n] = rbro->pchild[0], par->key[i + 1] = rbro->key[1]; // 将右兄弟的最小值提上去
            rbro->pchild[0] = rbro->pchild[1];
            rbro->delete_key(1);
            refresh(ptr);
            return;
        }
        // 没有富裕的情况，可能会改变头节点指针哦.
        node<T> *l = (rbro ? rbro : lbro), *r = ptr;
        if (l == rbro)
            std::swap(l, r);
        i = (rbro ? (i + 1) : i);                // i为两者中间夹的key的位置编号
        ptr = node<T>::merge(l, r, par->key[i]); // merge了以后必须更新ptr，因为原来的可能被释放了
        refresh(ptr);
        if (par == head && par->n == 1) // 头节点只有一个关键字了,要将其删除
        {
            delete head;
            head = ptr;
            head->par = NULL;
            return;
        }
        par->delete_key(i);
        par->pchild[i - 1] = ptr; // 把合并后的结点连上去
        merge(par);
    }
    node<T> *min_key(node<T> *root)
    {
        if (root == NULL)
            throw "mid_key ERROR:从终端结点进入函数！";
        if (root->pchild[0] == NULL)
            return root;
        else
            return min_key(root->pchild[0]);
    }

public:
    result<T> find(const T &value) const
    {
        return find(value, head);
    }
    result<T> find(const T &value, node<T> *root) const // 查找成功返回true
    {
        node<T> *ptr = root, *last = NULL;
        deque<int> que;
        bool found = false;
        int i = -1;
        while (ptr && !found)
        {
            T *key = ptr->key, n = ptr->n;
            i = upper_bound(key + 1, key + n + 1, value) - key - 1; // 找到大于value的第一个值的位置的前趋
            if (i > 0 && key[i] == value)
                found = true;
            else
            {
                last = ptr;
                ptr = ptr->pchild[i];
                que.push_back(i);
            }
        }
        if (found)
            return result<T>(ptr, i, true, que);
        else
            return result<T>(last, i, false, que); // 没找到返回应该插入的位置，即 key的i - i+1之间
    }
    bool insert(const T &value) // 插入失败说明已经存在
    {
        result<T> pos = find(value);
        if (pos.tag)
            return false;
        if (head == NULL)
        {
            head = new node<T>(1, NULL);
            head->key[1] = value;
            return true;
        }
        // 因为查找返回的位置一定是终端结点，所以才能直接插入value
        node<T> *ptr = pos.p;
        ptr->insert_key(value);
        if (ptr->too_big())
            split(ptr); // 需要分裂
        return true;
    }
    void show_in(node<T> *ptr, deque<int> &num)
    {
        if (!ptr)
            return;
        result<T> res;
        res.path = num, res.p = ptr;
        res.show();
        for (int i = 0; i <= ptr->n; i++)
            if (ptr->pchild[i])
            {
                num.push_back(i);
                show_in(ptr->pchild[i], num);
                num.pop_back();
            }
    }
    bool erase(const T &value) { return erase(value, head); }
    bool erase(const T &value, node<T> *root) // 在root子树中删除
    {
        result<int> res = find(value, root);
        if (!res.tag)
            return false; // B-树里面没有对应关键字，删除失败
        // 删除
        // 1.找到要删除的关键字对应的结点
        // 2.若该节点为终端结点，那么直接删除关键字，不是的话，就把关键字对应的右子树的最小值拿过来，同时在右子树删除它
        node<T> *ptr = res.p;
        int i = res.i;
        if (ptr->pchild[0] == NULL)
        {
            ptr->delete_key(i); // 删除的时候个数肯定不会超标，delete_key不会下标越界
            merge(ptr);
        }
        else
        {
            node<T> *k = min_key(ptr->pchild[i]); // 右子树最小值
            ptr->key[i] = k->key[1];
            erase(k->key[1], ptr->pchild[i]);
        }
        return true;
    }
    void show()
    {
        deque<int> que;
        show_in(head, que);
    }
};
int main()
{
    // freopen("input.txt", "r", stdin);
    BMTree<int> tree;
    int x;
    while (true)
    {
        cout << "1.插入关键字 \n2.删除关键字 \n3.查找关键字 \n4.层次遍历输出B-树所有结点 \n5.结束程序\n";
        cin >> x;
        result<int> res;
        switch (x)
        {
        case 1:
            cout << "输入要插入的关键字：";
            cin >> x;
            if (!tree.insert(x))
                cout << "插入失败\n";
            // tree.show();
            cout << endl;
            break;
        case 2:
            cout << "输入要删除的关键字：";
            cin >> x;
            cout << (tree.erase(x) ? "删除成功！" : "删除失败，结点不存在") << endl;
            break;
        case 3:
            cout << "输入要查找的关键字：";
            cin >> x;
            res = tree.find(x);
            if (!res.tag)
                cout << "关键字不存在！\n";
            else
                res.show();
            break;
        case 4:
            tree.show(); // 深度遍历,还需要改成宽度优先遍历
            break;
        case 5:
            return 0;
        default:
            break;
        }
    }
    return 0;
}
