

```C++
#include <iostream>
#include <cstring>
using namespace std;

const int N = 510, INF = 0x3f3f3f3f;
int n, m;
int g[N][N];
int dist[N];
bool st[N];

int prim() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    int res = 0;
    for (int i = 0; i < n; ++i) {
        int t = -1;
        for (int j = 1; j <= n; ++j) {
            if (!st[j] && (t == -1 || dist[t] > dist[j]))
                t = j;
        }
        st[t] = true;
        if (dist[t] == INF) return -1;
        res += dist[t];
        for (int j = 1; j <= n; ++j) {
            dist[j] = min(dist[j], g[t][j]);   
            //这里不同于Dijkstra算法，这里要求的是点到集合的最短距离
            //Dijkstra算法中是g[t][j] + dist[t]求的是点到源点的最短距离
        }
    }
    return res;
}
int main() {
    memset(g, 0x3f, sizeof g);
    scanf("%d%d", &n, &m);
    while (m--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        g[a][b] = g[b][a] = min(g[a][b], c);
    }
    int t = prim();
    if (t == -1) puts("impossible");
    else cout << t << endl;
    return 0;
}
```

