> Kruskal裸题
```c++
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 110, M = 210;
int n, m;
int p[N];
struct Edge{
    int a, b, w;
    bool operator< (const Edge& t) const {
        return w < t.w;
    }
}edges[M];

int find(int u) {
    if (p[u] != u) p[u] = find(p[u]);
    return p[u];
}
int kruskal() {
    int res = 0;
    for (int i = 0; i < m; ++i) {
        Edge& t = edges[i];
        int a = find(t.a), b = find(t.b), w = t.w;
        if (a != b) p[a] = b;
        else res += w;
    }
    return res;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) p[i] = i;
    for (int i = 0; i < m; ++i) cin >> edges[i].a >> edges[i].b >> edges[i].w;
    sort(edges, edges + m);
    cout << kruskal() << endl;
    return 0;
}

```