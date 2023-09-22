#include <iostream>
using namespace std;
#include <vector>

vector<int> Next(string pattern)
{
    vector<int> next;
    next.push_back(0); // next容器的首位必定为0
    for (int i = 1, j = 0; i < pattern.length(); i++)
    {
        while (j > 0 && pattern[j] != pattern[i])
        {
            j = next[j - 1];
        }
        if (pattern[i] == pattern[j])
        {
            j++;
        }
        next.push_back(j);
    }
    return next;
}

int main()
{
    string pattern = "ABABC", target = "ABABA ABABCABAA CAADB ABABCAADKDABC";
    vector<int> next = Next(pattern);

    for (int i = 0, j = 0; i < target.length(); i++)
    {
        while (j > 0 && target[i] != pattern[j])
        {
            j = next[j - 1];
        }
        if (target[i] == pattern[j])
        {
            j++;
        }
        if (j == pattern.length())
        {
            cout << "Found pattern at " << i - j << " position" << endl;
            j = next[j - 1];
        }
    }
    return 0;
}
