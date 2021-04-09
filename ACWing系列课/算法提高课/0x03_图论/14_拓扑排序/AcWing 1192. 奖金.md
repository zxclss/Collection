## `差分约束`求`最长路`，针对`不同数据`的对应`解法`
1. 边权`无限制`
   `spfa算法`，时间复杂度$O(nm)$
2. 边权`非负`
   `tarjan算法`，时间复杂度$O(n + m)$
3. 边权$>0$
   `topsort算法`，时间复杂度$O(n + m)$


```c++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 10010, M = 20010;
int n, m;
int h[N], e[M], ne[M], w[M], idx;
int din[N], q[N];
int dist[N];

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
bool topsort() {
    int hh = 0, tt = -1;
    for (int i = 1; i <= n; ++i)
        if (!din[i])
            q[++tt] = i;
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (--din[j] == 0) q[++tt] = j;
        }
    }
    return tt == n - 1;
}
int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    while (m--) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(b, a, 1);
        ++din[a];
    }
    if (!topsort()) puts("Poor Xed");
    else {
        //差分约束，最小值求最长路
        for (int i = 1; i <= n; ++i)
            if (din[i] == 0) dist[i] = 100;
        for (int u = 0; u < n; ++u) {
            int t = q[u];
            for (int i = h[t]; ~i; i = ne[i]) {
                int j = e[i];
                dist[j] = max(dist[j], dist[t] + w[i]);
            }
        }
        int res = 0;
        for (int i = 1; i <= n; ++i) res += dist[i];
        cout << res << endl;
    }
    return 0;
}
```