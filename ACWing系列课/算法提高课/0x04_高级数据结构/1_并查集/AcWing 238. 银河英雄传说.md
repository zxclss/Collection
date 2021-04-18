> 并查集：用到根结点的距离维护当前战舰到顶部的战舰数量（前缀和思想）
```c++
#include <iostream>
#include <cstdio>

using namespace std;

const int N = 30010;
int n;
int p[N], s[N], d[N];

int find(int u)
{
    if (p[u] != u)
    {
        int t = find(p[u]);
        d[u] += d[p[u]];
        p[u] = t;
    }
    return p[u];
}
int main() {
    scanf("%d", &n);
    for (int i = 0; i < N; ++i) p[i] = i, s[i] = 1;
    while (n--) {
        char op[2];
        int a, b;
        scanf("%s%d%d", op, &a, &b);
        int pa = find(a), pb = find(b);
        if (op[0] == 'M')
        {
            p[pa] = pb;
            d[pa] += s[pb];
            s[pb] += s[pa];
        }
        else
        {
            if (pa != pb) puts("-1");
            else printf("%d\n", abs(d[a] - d[b]) - 1);
        }
    }
}
```