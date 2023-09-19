#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct edge
{
    int u, v;
    int weight;
};
vector<int> father; // 记录每个节点的父亲
vector<int> result; // 存储最后获得的各条边

bool compare(edge a, edge b)
{
    return a.weight < b.weight;
}

int findfather(int a)
{
    while (a != father[a])
    {
        a = father[a];
    }
    return a;
}
void kruskal(int n, vector<edge> Edge)
{
    father.resize(n);
    sort(Edge.begin(), Edge.end(), compare);
    for (int i = 0; i < n; ++i)
    {
        father[i] = i;
    }
    for (int i = 0; i < Edge.size() && result.size() < n - 1; ++i)
    {
        int u = Edge[i].u;
        int v = Edge[i].v;
        if (findfather(u) != findfather(v)) // 判断父节点是否相同
        {
            result.push_back(Edge[i].weight);
            father[findfather(u)] = father[findfather(v)]; // 将两点并入一个集合中
        }
    }
    if (result.size() != n - 1)
    {
        cout << result.size() << "该图不连通" << endl;
        return;
    }
    else
    {
        cout << "最小生成树的各边如下：" << endl;
        for (int i = 0; i < result.size(); ++i)
        {
            cout << result[i] << endl;
        }
    }
}

int main()
{
    int n, m;
    cout << "输入结点数：";
    cin >> n;
    cout << "输入边数：";
    cin >> m;
    vector<edge> Edge(m);
    cout << "输入各条边的信息：" << endl;
    for (int i = 0; i < m; ++i)
    {
        cin >> Edge[i].u >> Edge[i].v >> Edge[i].weight;
    }
    kruskal(n, Edge);
    return 0;
}
