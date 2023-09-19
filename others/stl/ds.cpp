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
    m.emplace_hint(m.end(), 11, 11); // insert at the position of the hint // {1 1} {3 3} {4 4} {10 10} {11 11}

    // Deletion // {3 3} {4 4} {10 10} {11 11}
    m.erase(1);
    m.erase(m.begin()); // will erase the smallest key

    // Find // 5
    *m.find(4);
    *m.lower_bound(3); // 3
    *m.upper_bound(3); // 4

    // Count // 1
    m.count(4);

    // Min/Max // 2 10
    *m.begin();
    *m.rbegin();

    // Compare function
    m.key_comp()(1, 2);                                         // return the comparison function // true
    m.value_comp()(std::make_pair(1, 2), std::make_pair(2, 1)); // true

    // Pair of iterators
    m.equal_range(3); // this function is equivalent to std::make_pair(c.lower_bound(val), c.upper_bound(val)) (but is faster than making the calls separately).// {3 3} {4 4}
}

void testUnorderedMap()
{
    std::unordered_map<int, int> m = {{2, 2}, {1, 1}, {3, 3}, {4, 4}};

    // Insertion // {11 11}
    m.emplace(10, 10);
    m.emplace_hint(m.end(), 11, 11); // insert at the position of the hint // {1 1} {3 3} {4 4} {10 10} {11 11}

    // Deletion // {10 10} {2 2} {3 3} {4 4}
    m.erase(1);
    m.erase(m.begin()); // will erase the first key

    // Find // 4
    *m.find(4);

    // Count // 1
    m.count(4);

    // Min/Max // 2 10
    *m.begin();

    // Hash function
    m.hash_function()(1); // return the hash function // 1

    // Pair of iterators
    m.equal_range(3); // this function is equivalent to std::make_pair(c.lower_bound(val), c.upper_bound(val)) (but is faster than making the calls separately).// {3 3} {4 4}

    // Buckets
    m.load_factor();     // return the average number of elements per bucket // 0.5
    m.max_load_factor(); // return the maximum load factor // 1
}

void testStack()
{
    std::stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.pop();   // 2
    s.top();   // 2
    s.empty(); // false
    s.size();  // 2
}

int main()
{
    // testVector();
    // testSet();
    // testMap();
    // testUnorderedMap();
    // testStack();
}