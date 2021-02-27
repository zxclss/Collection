

```C++
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 2e5 + 10, INF = 0x3f3f3f3f;
struct Edge{
    int a, b, w;
    bool operator< (Edge& e) {
        return w < e.w;
    }
}edges[N];
int n, m;
int p[N];

int find(int a) {
    if (p[a] != a) p[a] = find(p[a]);
    return p[a];
}

int kruskal() {
    for (int i = 1; i <= n; ++i) p[i] = i; //并查集初始化
    sort(edges, edges + m);   //权重排序
    int res = 0, cnt = 0;
    for (int i = 0; i < m; ++i) {
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;
        a = find(a), b = find(b);
        if (a != b) {
            p[a] = b;
            res += w;
            ++cnt;
        }
    }
    if (cnt < n - 1) return INF;
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        edges[i] = {a, b, c};
    }
    int t = kruskal();
    if (t == INF) puts("impossible");
    else cout << t << endl;
    return 0;
}
```

