#include <bits/stdc++.h>
using namespace std;
long long n, m;
long long s[500050], d[500050];
// 必须从1开始
// d[x] 就掌管长度为lowbit（x）的范围，即掌管范围是[x-lowbit(x)+1,x] // (x-lowbit(x),x]
long long lowbit(long long x)
{
    return x & (-x);
}

void add(long long x, long long k)
{
    while (x <= n)
    {
        d[x] += k;
        x += lowbit(x);
    }
}

long long query(long long x)
{ // 求1~x的区间和
    long long ans = 0;
    while (x)
    {
        ans += d[x];
        x -= lowbit(x);
    }
    return ans;
}
int main()
{
    cin >> n >> m;
    for (long long i = 1; i <= n; i++)
    {
        cin >> s[i];
    }
    for (long long i = 1; i <= n; i++)
    {
        add(i, s[i] - s[i - 1]);
    }
    for (long long i = 1; i <= m; i++)
    {
        long long op;
        cin >> op;
        if (op == 1)
        {
            long long x, y, k;
            cin >> x >> y >> k;
            add(x, k);
            add(y + 1, -k);
        }
        else
        {
            long long x;
            cin >> x;
            cout << query(x) << endl;
        }
    }
    return 0;
}