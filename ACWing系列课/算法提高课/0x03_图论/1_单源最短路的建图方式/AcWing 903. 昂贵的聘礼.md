```c++
#include <iostream>
#include <cstring>
using namespace std;

//这题我们建立一个虚拟起点在'0'处
//直接兑换商品'i'的行为，看作从'0'直接连一条到'i'的边

const int N = 110, INF = 0x3f3f3f3f;
int n, m;
int g[N][N];
int dist[N], level[N];
bool st[N];

int dijkstra(int l, int r) {
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    dist[0] = 0;
    for (int i = 0; i < n + 1; ++i) {
        int t = -1;
        for (int j = 0; j <= n; ++j)
            if (!st[j] && (t == -1 || dist[t] > dist[j]))
                t = j;
        st[t] = true;
        for (int j = 1; j <= n; ++j) {
            //阶级在枚举的区间内，才能走这条边兑换商品
            if (level[j] >= l && level[j] <= r)
                dist[j] = min(dist[j], dist[t] + g[t][j]);
        }
    }
    return dist[1];
}
int main() {
    memset(g, 0x3f, sizeof g);
    cin >> m >> n;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> g[0][i] >> level[i] >> x;
        while (x--) {
            int t, v;
            cin >> t >> v;
            g[t][i] = v;
        }
    }
    int res = INF;
    //枚举阶级的区间
    for (int l = level[1] - m; l <= level[1]; ++l) {
        int r = l + m;
        res = min(res, dijkstra(l, r));
    }
    cout << res << endl;
    return 0;
}
```

