
#include <bits/stdc++.h>
#define MOD 10000000007
#define INF 0x3f3f3f3f
using namespace std;
typedef long long LL;
const int maxn = 2000005;
int n, m, s;
// idx表示边的序数，e存终点，w存权值，h存表头，next存下一个点（h和next形成了链表）
// idx其实并没有实质性意义，只是用于确定一条边的前驱、后驱和权值(便于调用及确定与其顶点的关系)
int idx, e[maxn], w[maxn], h[maxn], ne[maxn];
int dis[maxn], vis[maxn]; // 距离，标记

struct Node
{
    int dis, x; // 距离和当前点
    // 重载运算符（从小到大排序）
    bool operator<(Node p) const
    {
        return dis > p.dis;
    }
    Node(int dis, int x) : dis(dis), x(x) {}
};

// 快读
inline int read()
{
    int date = 0, w = 1;
    char c;
    c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        date = date * 10 + (c - '0');
        c = getchar();
    }
    return date * w;
}

// 邻接表(顶点为表头，后面跟着的都是该顶点为起点的边)
void add(int a, int b, int c)
{
    e[++idx] = b;
    w[idx] = c;
    ne[idx] = h[a]; // 同一个起点的边形成邻接表关系
    h[a] = idx;
}

void dijkstra()
{
    memset(dis, INF, sizeof(dis)); // 初始化
    priority_queue<Node> q;        // 按照结构体中的重载符进行排序（从小到大排序，先将dis小的出队）
    dis[s] = 0;                    // 初始化起点
    Node u(dis[s], s);
    q.push(u);
    while (!q.empty())
    {
        Node u = q.top();
        q.pop();

        if (vis[u.x])
            continue; // 已标记过的点，即这个点为起点的这条链已走完
        vis[u.x] = 1; // 标记

        // for(表头;链尾非NULL;链的下一个结点)
        for (int i = h[u.x]; i; i = ne[i])
        {
            if (dis[e[i]] > dis[u.x] + w[i])
            {
                dis[e[i]] = dis[u.x] + w[i];
                Node v(dis[e[i]], e[i]); // dis[终点]，终点（距离起点最近）
                q.push(v);
            }
        }
    }
}

int main()
{
    n = read(), m = read(), s = read();
    for (int i = 1; i <= m; i++)
    {
        int a = read(), b = read(), c = read();
        add(a, b, c); // 建立邻接表关系（以边为单位）
    }
    /*for(int i=0; i<=n; i++)
    cout<<h[i]<<" "<<e[i]<<" "<<w[i]<<" "<<next[i]<<endl;*/

    dijkstra();

    for (int i = 1; i <= n; i++)
        cout << dis[i] << " ";
    return 0;
