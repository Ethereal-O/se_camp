#include "bits/stdc++.h"

class TestSort
{
public:
    int a;
    int b;
    bool operator<(const TestSort &t) const
    {
        return a < t.a || (a == t.a && b < t.b);
    }
    bool operator>(const TestSort &t) const
    {
        return a > t.a || (a == t.a && b > t.b);
    }
    friend std::ostream &operator<<(std::ostream &os, const TestSort &t)
    {
        os << "{" << t.a << " " << t.b << "}";
        return os;
    }
};

void sort1(std::vector<int> &v, bool isIncr = true)
{
    if (isIncr)
        std::sort(v.begin(), v.end());
    else
        std::sort(v.begin(), v.end(), std::greater<int>());
}

void sort1(std::vector<TestSort> &v, bool isIncr = true)
{
    // use operator< or operator>
    if (isIncr)
        std::sort(v.begin(), v.end());
    else
        std::sort(v.begin(), v.end(), std::greater<TestSort>());
}

void sort2(std::vector<TestSort> &v, bool isIncr = true)
{
    int test = 1;
    // use lambda
    if (isIncr)
        std::sort(v.begin(), v.end(), [&](const TestSort &t1, const TestSort &t2)
                  { std::cout << test++ << std::endl;
                    return t1.a < t2.a || (t1.a == t2.a && t1.b < t2.b); });
    else
        std::sort(v.begin(), v.end(), [&](const TestSort &t1, const TestSort &t2)
                  { return t1.a > t2.a || (t1.a == t2.a && t1.b > t2.b); });
}

void sort3(std::vector<TestSort> &v, bool isIncr = true)
{
    // use priority_queue
    if (isIncr)
    {
        std::priority_queue<TestSort, std::vector<TestSort>, std::greater<TestSort>> q;
        for (auto i : v)
            q.push(i);
        v.clear();
        while (!q.empty())
        {
            v.push_back(q.top());
            q.pop();
        }
    }
    else
    {
        std::priority_queue<TestSort, std::vector<TestSort>, std::less<TestSort>> q;
        for (auto i : v)
            q.push(i);
        v.clear();
        while (!q.empty())
        {
            v.push_back(q.top());
            q.pop();
        }
    }
}

void sort4(std::vector<TestSort> &v, bool isIncr = true)
{
    // use priority_queue and lambda
    if (isIncr)
    {
        auto cmp = [&](const TestSort &t1, const TestSort &t2)
        { return t1.a > t2.a || (t1.a == t2.a && t1.b > t2.b); };

        std::priority_queue<TestSort, std::vector<TestSort>, decltype(cmp)> q(cmp);
        for (auto i : v)
            q.push(i);
        v.clear();
        while (!q.empty())
        {
            v.push_back(q.top());
            q.pop();
        }
    }
    else
    {
        auto cmp = [&](const TestSort &t1, const TestSort &t2)
        { return t1.a < t2.a || (t1.a == t2.a && t1.b < t2.b); };

        std::priority_queue<TestSort, std::vector<TestSort>, decltype(cmp)> q(cmp);
        for (auto i : v)
            q.push(i);
        v.clear();
        while (!q.empty())
        {
            v.push_back(q.top());
            q.pop();
        }
    }
}

void sort5(std::vector<TestSort> &v, bool isIncr = true)
{
    // use set
    if (isIncr)
    {
        std::set<TestSort, std::less<TestSort>> s;
        for (auto i : v)
            s.insert(i);
        v.clear();
        for (auto i : s)
            v.push_back(i);
    }
    else
    {
        std::set<TestSort, std::greater<TestSort>> s;
        for (auto i : v)
            s.insert(i);
        v.clear();
        for (auto i : s)
            v.push_back(i);
    }
}

void sort6(std::vector<TestSort> &v, bool isIncr = true)
{
    // use set and lambda
    if (isIncr)
    {
        auto cmp = [&](const TestSort &t1, const TestSort &t2)
        { return t1.a < t2.a || (t1.a == t2.a && t1.b < t2.b); };

        std::set<TestSort, decltype(cmp)> s(cmp);
        for (auto i : v)
            s.insert(i);
        v.clear();
        for (auto i : s)
            v.push_back(i);
    }
    else
    {
        auto cmp = [&](const TestSort &t1, const TestSort &t2)
        { return t1.a > t2.a || (t1.a == t2.a && t1.b > t2.b); };

        std::set<TestSort, decltype(cmp)> s(cmp);
        for (auto i : v)
            s.insert(i);
        v.clear();
        for (auto i : s)
            v.push_back(i);
    }
}

void sort7(std::vector<TestSort> &v, bool isIncr = true)
{
    if (isIncr)
    {
        std::make_heap(v.begin(), v.end(), std::less<TestSort>());
        std::sort_heap(v.begin(), v.end(), std::less<TestSort>());
    }
    else
    {
        std::make_heap(v.begin(), v.end(), std::greater<TestSort>());
        std::sort_heap(v.begin(), v.end(), std::greater<TestSort>());
    }
}

void binarySearch(std::vector<TestSort> &v)
{
    std::sort(v.begin(), v.end());                                                    // sort from less to greater
    std::cout << *std::upper_bound(v.begin(), v.end(), TestSort{3, 4}) << std::endl;  // so we can use upper_bound to find the first element greater than {3,4} // returns {6,2}
    std::cout << *std::lower_bound(v.begin(), v.end(), TestSort{3, 4}) << std::endl;  // and lower_bound to find the first element not less than {3,4} // returns {3,4}
    std::cout << std::binary_search(v.begin(), v.end(), TestSort{3, 4}) << std::endl; // returns true

    std::sort(v.begin(), v.end(), std::greater<TestSort>());                                                   // sort from greater to less
    std::cout << *std::upper_bound(v.begin(), v.end(), TestSort{3, 4}, std::greater<TestSort>()) << std::endl; // so we can use upper_bound to find the first element less than {3,4} // returns {3,3}
    std::cout << *std::lower_bound(v.begin(), v.end(), TestSort{3, 4}, std::greater<TestSort>()) << std::endl; // and lower_bound to find the first element not greater than {3,4} // returns {3,4}
    std::cout << std::binary_search(v.begin(), v.end(), TestSort{3, 4}, [&](const TestSort &t1, const TestSort &t2)
                                    {std::cout<<"comparing "<<t1<<" "<<t2<<std::endl;return t1 > t2; })
              << std::endl; // returns true
}

std::vector<TestSort> topN1(std::vector<TestSort> &v, int n, bool isIncr = true) // because we will pop_back, so we need to copy the vector
{
    std::vector<TestSort> res;
    if (isIncr)
    {
        std::make_heap(v.begin(), v.end(), std::less<TestSort>());
        for (int i = 0; i < n; i++)
        {
            res.push_back(v.front());
            std::pop_heap(v.begin(), v.end() - i, std::less<TestSort>());
        }
    }
    else
    {
        std::make_heap(v.begin(), v.end(), std::greater<TestSort>());
        for (int i = 0; i < n; i++)
        {
            res.push_back(v.front());
            std::pop_heap(v.begin(), v.end() - i, std::greater<TestSort>());
        }
    }
    return res;
}

std::vector<TestSort> topN2(std::vector<TestSort> v, int n, bool isIncr = true) // because we will pop_back, so we need to copy the vector
{
    std::vector<TestSort> res;
    if (isIncr)
    {
        std::make_heap(v.begin(), v.end(), std::less<TestSort>());
        for (int i = 0; i < n; i++)
        {
            res.push_back(v.front());
            std::pop_heap(v.begin(), v.end(), std::less<TestSort>());
            v.pop_back();
        }
    }
    else
    {
        std::make_heap(v.begin(), v.end(), std::greater<TestSort>());
        for (int i = 0; i < n; i++)
        {
            res.push_back(v.front());
            std::pop_heap(v.begin(), v.end(), std::greater<TestSort>());
            v.pop_back();
        }
    }
    return res;
}

std::vector<TestSort> topN3(std::vector<TestSort> &v, int n, bool isIncr = true) // here don't need to copy the vector, but need copy too
{
    std::vector<TestSort> res;
    if (isIncr)
    {
        std::priority_queue<TestSort, std::vector<TestSort>, std::less<TestSort>> q;
        for (auto i : v)
            q.push(i);
        for (int i = 0; i < n; i++)
        {
            res.push_back(q.top());
            q.pop();
        }
    }
    else
    {
        std::priority_queue<TestSort, std::vector<TestSort>, std::greater<TestSort>> q;
        for (auto i : v)
            q.push(i);
        for (int i = 0; i < n; i++)
        {
            res.push_back(q.top());
            q.pop();
        }
    }
    return res;
}

int main()
{
    // std::vector<int> v = {1, 5, 3, 2, 4};
    std::vector<TestSort> v = {{1, 2}, {3, 4}, {3, 3}, {2, 5}, {6, 2}};
    sort1(v);
    for (auto i : v)
        std::cout << i << " ";
    std::cout << std::endl;

    auto vTopN = topN1(v, 3);
    for (auto i : vTopN)
        std::cout << i << " ";
    std::cout << std::endl;

    binarySearch(v);
}