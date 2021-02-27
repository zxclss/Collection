> 这题是求多个起点到同一个终点1的最短距离的最大值
>
> 可以用n遍Dijkstra
>
> 因此数据范围较小，我们直接Floyd求出所有点之间的距离即可

```c++
#include <iostream>
#include <cstring>
using namespace std;

const int N = 110, INF = 0x3f3f3f3f;
int n, m;
int dist[N][N];

void floyd() {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}
int main() {
    memset(dist, 0x3f, sizeof dist);
    cin >> n >> m;
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = dist[b][a] = min(dist[a][b], c);
    }
    
    floyd();
    
    int res = 0;
    for (int i = 1; i <= n; ++i)
        if (dist[1][i] == INF) {
            cout << -1 << endl;
            return 0;
        } else {
            res = max(res, dist[1][i]);
        }
    cout << res << endl;
    return 0;
}
```

