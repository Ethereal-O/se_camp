#include <iostream>
#include <vector>

using namespace std;

template <class T>
class MaxHeap
{
public:
    MaxHeap(int _capacity = 10)
    {
        size = 0;
        capacity = _capacity;
        heap = new T[capacity];
    }
    ~MaxHeap()
    {
        delete[] heap;
    }

    bool empty()
    {
        if (size == 0)
            return true;
        return false;
    }

    void Insert(T value)
    {
        if (size < capacity)
        {
            heap[size++] = value;
            int index = size;
            while (index > 1)
            {
                if (heap[index] > heap[index / 2])
                    swap(heap[index], heap[index / 2]);
                index /= 2;
            }
        }
        else
            return;
    }

    void DeleteMax()
    {
        if (size == 0)
            return;
        swap[heap[1], heap[size--]]; // 用最后一个结点将第一个结点替换，替换结束后最后一个结点为原本第一个结点，size--表示删除最后一个结点，
        int index = 1;               // 也就是将第一个节点间接删除
        while (index <= size)
        {
            int p = 2 * index;
            if (p < size && heap[p] < heap[p + 1]) // 找孩子节点中最大的一个
                p++;
            swap(heap[p], heap[index]);
            index = p; // 继续向下调整
        }
    }

    T Maxvalue()
    {
        if (empty())
            return -1;
        return heap[1];
    }

private:
    int size;
    int capacity;
    T *heap;
};

void BuildHeap(int res[], int size) // 用数组创建堆
{
    for (int i = size / 2; i >= 1; --i)
    {
        int temp = res[i];
        int index = 2 * i;
        while (index <= size)
        {
            if (index < size && res[index] < res[index + 1])
                index++;
            if (res[index] > temp)
            {
                res[index / 2] = res[index];
                index *= 2;
            }
            else
                break;
        }
        res[index / 2] = temp;
    }
}

template <class T>
void TestMaxHeap()
{
    int res[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    BuildHeap(res, 9);
    for (int i = 1; i < 10; ++i)
    {
        cout << res[i] << " ";
    }
}
int main()
{
    TestMaxHeap<int>();
    system("pause");
    return 0;
}
