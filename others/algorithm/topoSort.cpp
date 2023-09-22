#include <bits/stdc++.h>
using namespace std;

using Graph = vector<vector<int>>; // 邻接表

struct TopoSort
{
    enum class Status : uint8_t
    {
        to_visit,
        visiting,
        visited
    };

    const Graph &graph;
    const int n;
    vector<Status> status;
    vector<int> order;
    vector<int>::reverse_iterator it;

    TopoSort(const Graph &graph)
        : graph(graph),
          n(graph.size()),
          status(n, Status::to_visit),
          order(n),
          it(order.rbegin()) {}

    bool sort()
    {
        for (int i = 0; i < n; ++i)
        {
            if (status[i] == Status::to_visit && !dfs(i))
                return false;
        }
        return true;
    }

    bool dfs(const int u)
    {
        status[u] = Status::visiting;
        for (const int v : graph[u])
        {
            if (status[v] == Status::visiting)
                return false;
            if (status[v] == Status::to_visit && !dfs(v))
                return false;
        }
        status[u] = Status::visited;
        *it++ = u;
        return true;
    }
};