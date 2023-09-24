// 202402386
#include <bits/stdc++.h>

struct CostTree
{
    CostTree *notReturn;
    CostTree *IsReturn;
    int notReturnCost;
    int IsReturnCost;
};

int N, M, Q, P;

std::vector<std::vector<int>> graph;

std::vector<std::vector<int>> dist;

std::vector<int> path;

std::vector<int> PVector;

CostTree *root;

int minCost = INT_MAX;

class MersenneTwister
{
public:
    MersenneTwister()
    {
        index = 0;
        mt[0] = 2023; // seed
        for (int i = 1; i < 624; ++i)
        {
            mt[i] = (0x6C078965 * (mt[i - 1] ^ (mt[i - 1] >> 30)) + i) & 0xFFFFFFFF;
        }
    }

    unsigned int generate()
    {
        if (index == 0)
        {
            for (int i = 0; i < 624; ++i)
            {
                unsigned int y =
                    ((mt[i] & 0x80000000) + (mt[(i + 1) % 624] & 0x7FFFFFFF)) & 0xFFFFFFFF;
                mt[i] = mt[(i + 397) % 624] ^ (y >> 1);
                if (y % 2 != 0)
                {
                    mt[i] ^= 0x9908B0DF;
                }
            }
        }

        unsigned int y = mt[index];
        y ^= (y >> 11);
        y ^= ((y << 7) & 0x9D2C5680);
        y ^= ((y << 15) & 0xEFC60000);
        y ^= (y >> 18);

        index = (index + 1) % 624;
        return y;
    }

    unsigned int mt[624];
    int index;
};

// 读取文件
bool read_file(const std::string &filename, std::string &to_str)
{
    std::ifstream ifs(filename);
    if (!ifs.is_open())
        return false;
    to_str = std::string((std::istreambuf_iterator<char>(ifs)),
                         (std::istreambuf_iterator<char>()));
    ifs.close();
    return true;
}

// 写入文件
void write_file(const std::string &filename, const std::string &content)
{
    std::ofstream ofs(filename);
    ofs << content;
    ofs.close();
}

// 建图
void BuildGraph()
{
    std::string file_path;
    std::cin >> file_path;
    std::string content;
    read_file(file_path, content);
    std::stringstream ss(content);
    ss >> N >> M >> Q >> P;
    graph = std::vector<std::vector<int>>(N, std::vector<int>(N, -1));
    dist = std::vector<std::vector<int>>(N, std::vector<int>(N, -1));

    // 读入距离
    for (int i = 0; i < M; i++)
    {
        int x, y, w;
        ss >> x >> y >> w;
        graph.at(x).at(y) = w;
    }

    // 读入乘客位置
    for (int i = 0; i < P; i++)
    {
        int p;
        ss >> p;
        PVector.push_back(p);
    }

    // 计算最多出边的位置
    int max_point = -1;
    int max_num = 0;
    for (int j = 0; j < N; j++)
    {
        int num = 0;
        for (int i = 0; i < N; i++)
        {
            if (graph[i][j] >= 0)
                num++;
        }
        if (num > max_num)
        {
            max_point = j;
            max_num = num;
        }
    }

    std::cout << max_point << " " << max_num << std::endl;
}

// dijkstra算法
void dijkstra(int from)
{
    auto cmp = [&](const std::pair<int, int> &p1, const std::pair<int, int> &p2)
    {
        return p1.second > p2.second || (p1.second == p2.second && p1.first > p2.first);
    };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> q(cmp); // index, dist
    std::vector<int> visited(N, 0);
    q.push(std::make_pair(from, 0));
    while (!q.empty())
    {

        std::pair<int, int> u = q.top();
        q.pop();

        if (visited[u.first])
            continue;
        visited[u.first] = 1;

        for (int i = 0; i < N; i++)
        {
            if (graph[u.first][i] < 0 || dist[from][u.first] < 0)
                continue;
            if (dist[from][i] == -1 || dist[from][i] > dist[from][u.first] + graph[u.first][i])
            {
                dist[from][i] = dist[from][u.first] + graph[u.first][i];
                q.push(std::make_pair(i, dist[from][i]));
            }
        }
    }
}

// 计算最短路径
void ComputePath()
{
    for (int i = 0; i < N; i++)
    {
        dist[i][i] = 0;
    }

    for (int i = 0; i < N; i++)
    {
        dijkstra(i);
    }

    // 获取最长路
    int out_x = -1, out_y = -1, max_path = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (dist[i][j] > max_path)
            {
                out_x = i;
                out_y = j;
                max_path = dist[i][j];
            }
        }
    }

    std::cout << out_x << " " << out_y << " " << max_path << std::endl;
}

std::string intToString(int num)
{
    std::stringstream ss;
    ss << num;
    return ss.str();
}

// 随机游走
void RandomWalk()
{
    auto random_generater = MersenneTwister();
    path.clear();
    path.push_back(0);
    int passengers = 0;
    int now_point = 0;
    for (auto p : PVector)
    {
        // 随机游走直到达到p点
        while (now_point != p)
        {
            std::vector<int> all_path;
            for (int i = 0; i < N; i++)
            {
                if (graph[now_point][i] >= 0)
                {
                    all_path.push_back(i);
                }
            }
            int random_index = random_generater.generate() % all_path.size();
            now_point = all_path[random_index];
            path.push_back(now_point);
            if (now_point == 0)
            {
                passengers = 0;
            }
        }
        passengers++;
        // 此时必须回到0点
        if (passengers == Q)
        {
            while (now_point != 0)
            {
                std::vector<int> all_path;
                for (int i = 0; i < N; i++)
                {
                    if (graph[now_point][i] >= 0)
                    {
                        all_path.push_back(i);
                    }
                }

                int random_index = random_generater.generate() % all_path.size();
                now_point = all_path[random_index];
                path.push_back(now_point);
            }
            passengers = 0;
        }
    }
    // 最后回到0点
    if (now_point != 0)
    {
        while (now_point != 0)
        {
            std::vector<int> all_path;
            for (int i = 0; i < N; i++)
            {
                if (graph[now_point][i] >= 0)
                {
                    all_path.push_back(i);
                }
            }

            int random_index = random_generater.generate() % all_path.size();
            now_point = all_path[random_index];
            path.push_back(now_point);
        }
    }

    // 计算路程
    int cost = 0;
    for (int i = 0; i < path.size() - 1; i++)
    {
        cost += graph[path[i]][path[i + 1]];
    }
    std::cout << cost << std::endl;

    // 写入文件
    std::string s;
    for (int i = 0; i < path.size(); i++)
    {
        s += intToString(path[i]);
        s += '\n';
    }
    write_file("path.txt", s);
}

// 最大N个
std::vector<std::pair<int, int>> topN(std::vector<std::pair<int, int>> &v, int n)
{
    std::vector<std::pair<int, int>> res;
    std::make_heap(v.begin(), v.end(), [&](std::pair<int, int> &p1, std::pair<int, int> &p2)
                   { return p1.second < p2.second || (p1.second == p2.second && p1.first > p2.first); });
    for (int i = 0; i < n; i++)
    {
        res.push_back(v.front());
        std::pop_heap(v.begin(), v.end() - i, [&](std::pair<int, int> &p1, std::pair<int, int> &p2)
                      { return p1.second < p2.second || (p1.second == p2.second && p1.first > p2.first); });
    }
    return res;
}

// 路径分析
void PathAnalyze()
{
    std::vector<int> visited_num = std::vector<int>(N, 0);
    for (auto p : path)
    {
        visited_num[p]++;
    }

    std::vector<std::pair<int, int>> visited_sort; // index, num

    for (int i = 0; i < N; i++)
    {
        if (visited_num[i] > 0)
        {
            visited_sort.push_back(std::make_pair(i, visited_num[i]));
        }
    }

    auto topN3 = topN(visited_sort, 3);
    for (auto n : topN3)
    {
        std::cout << n.first << " " << n.second << std::endl;
    }
}

// 建立路径树-dfs
void buildCostTree(CostTree *t, int i, int pCost, int passengers)
{
    if (i >= PVector.size())
    {
        if (pCost + dist[PVector[i - 1]][0] < minCost)
            minCost = pCost + dist[PVector[i - 1]][0];
        return;
    }

    t = new CostTree();
    if (i > 0)
        t->IsReturnCost = pCost + dist[PVector[i - 1]][0] + dist[0][PVector[i]];
    else
        t->IsReturnCost = pCost + dist[0][PVector[i]];
    buildCostTree(t->IsReturn, i + 1, t->IsReturnCost, 1);
    if (passengers != Q)
    {
        if (i > 0)
            t->notReturnCost = pCost + dist[PVector[i - 1]][PVector[i]];
        else
            t->notReturnCost = pCost + dist[0][PVector[i]];
        buildCostTree(t->notReturn, i + 1, t->notReturnCost, passengers + 1);
    }
}

void BestPath()
{
    // 不是最优的
    // int cost = 0;
    // int passengers = 0;
    // int last_point = 0;
    // for (auto p : PVector)
    // {
    //     cost += dist[last_point][p];
    //     passengers++;
    //     last_point = p;
    //     if (passengers == Q)
    //     {
    //         passengers = 0;
    //         cost += dist[last_point][0];
    //         last_point = 0;
    //     }
    // }
    // if (last_point != 0)
    // {
    //     cost += dist[last_point][0];
    // }
    // std::cout << cost << std::endl;

    // 最优但超时
    buildCostTree(root, 0, 0, 1);
    std::cout << minCost << std::endl;
}

int main()
{
    BuildGraph();
    ComputePath();
    RandomWalk();
    PathAnalyze();
    BestPath();
}