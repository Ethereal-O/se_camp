#include "bits/stdc++.h"

// template <typename T>
// concept is_container = requires(T t) {
//     typename T::value_type;
//     typename T::iterator;
//     typename T::const_iterator;
//     t.begin();
//     t.end();
//     t.cbegin();
//     t.cend();
//     t.size();
//     t.empty();
// };

// template <typename T>
// // requires is_container<T>
// void print(T v)
// {
//     for (auto i : v)
//         std::cout << i << " ";
//     std::cout << std::endl;
// }

template <typename T>
// requires is_container<T>
void print(T v)
{
    for (auto i : v)
        std::cout << "{" << i.first << " " << i.second << "} ";
    std::cout << std::endl;
}

void testVector()
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Insertion // 1 11 2 3 4 5 6 7 8 9 10
    v.emplace_back(10);
    v.emplace(v.begin() + 1, 11);

    // Deletion // 1 2 3 4 5 6 7 8 9
    v.erase(v.begin() + 1);
    v.pop_back();

    // change value when iterating // 2 3 4 5 6 7 8 9 10
    for (auto &&i : v)
        i++;

    // Reverse // 10 9 8 7 6 5 4 3 2
    std::reverse(v.begin(), v.end());

    // Rotation // change middle to first // 9 8 7 6 5 4 3 2 10
    std::rotate(v.begin(), v.begin() + 1, v.end());

    // Find // 5
    *std::find(v.begin(), v.end(), 5);

    // Count // 1
    std::count(v.begin(), v.end(), 5);

    // Min/Max // 2 10
    *std::min_element(v.begin(), v.end());
    *std::max_element(v.begin(), v.end());

    // Sum // 64
    std::accumulate(v.begin(), v.end(), 10);
}

void testSet()
{
    std::set<int> s = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Insertion // 1 2 3 4 5 6 7 8 9 10 11
    s.emplace(10);
    s.emplace(11);

    // Deletion // 3 4 5 6 7 8 9 10 11
    s.erase(1);
    s.erase(s.begin());

    // Find // 5
    *s.find(5);

    // Count // 1
    s.count(5);

    // Min/Max // 2 10
    *s.begin();
    *s.rbegin();

    // Sum // 64
    std::accumulate(s.begin(), s.end(), 10);
}

void testMap()
{
    std::map<int, int> m = {{2, 2}, {1, 1}, {3, 3}, {4, 4}};

    // Insertion // {1 1} {2 2} {3 3} {4 4} {10 10} {11 11}
    m.emplace(10, 10);
    m.emplace(11, 11);

    // Deletion // {3 3} {4 4} {10 10} {11 11}
    m.erase(1);
    m.erase(m.begin()); // will erase the smallest key

    // Find // 5
    *m.find(5);

    // Count // 1
    m.count(5);

    // Min/Max // 2 10
    *m.begin();
    *m.rbegin();
}

int main()
{
    // testVector();
    // testSet();
    // testMap();
}