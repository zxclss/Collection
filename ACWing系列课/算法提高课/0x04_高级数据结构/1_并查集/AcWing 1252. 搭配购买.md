> 0-1背包 + 并查集
```c++
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 10010;
int n, m, s;
int p[N];
int v[N], w[N];
int f[N];

int find(int x)  // 并查集
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main()
{
    cin >> n >> m >> s;
    for (int i = 1; i <= n; ++i) cin >> v[i] >> w[i], p[i] = i;
    while (m -- )
    {
        int a, b;
        cin >> a >> b;
        int pa = find(a), pb = find(b);
        if (pa != pb)
        {
            p[pa] = pb;
            w[pb] += w[pa];
            v[pb] += v[pa];
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        if (p[i] != i) continue;
        for (int j = s; j >= v[i]; --j)
        {
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }
    printf("%d\n", f[s]);
    return 0;
}
```