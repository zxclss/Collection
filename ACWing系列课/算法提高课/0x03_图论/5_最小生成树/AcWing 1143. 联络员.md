> Kruskal变种题
```c++
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2010, M = 10010;
int n, k, m;
int p[N];
struct Edge{
    int a, b, w;
    bool operator< (const Edge& t) const {
        return w < t.w;
    };
}edges[M];

int find(int u) {
    if (p[u] != u) p[u] = find(p[u]);
    return p[u];
}
int kruskal() {
    int res = 0;
    for (int i = 0; i < m; ++i) {
        int a = find(edges[i].a), b = find(edges[i].b), w = edges[i].w;
        if (a != b) p[a] = b, res += w;
    }
    return res;
}
int main() {
    int res = 0;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) p[i] = i;
    while (k--) {
        int t, a, b, c;
        cin >> t >> a >> b >> c;
        if (t == 1) {
            p[find(a)] = find(b);
            res += c;
        } else {
            edges[m++] = {a, b, c};
        }
    }
    sort(edges, edges + m);
    res += kruskal();
    cout << res << endl;
    return 0;
}

```