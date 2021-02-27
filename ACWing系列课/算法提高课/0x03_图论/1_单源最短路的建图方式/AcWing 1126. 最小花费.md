```c++
#include <iostream>
using namespace std;

const int N = 2010;
int n, m, S, T;
double g[N][N];
double dist[N];
bool st[N];

void dijkstra() {
    //dist初始化为0，表示没有搜到的情况下，起点S往该点t转账后，t得不到钱
    dist[S] = 1;//起点没有被收手续费
    for (int i =  0; i < n; ++i) {
        int t = -1;
        for (int j = 1; j <= n; ++j) {
            if (!st[j] && (t == -1 || dist[t] < dist[j])) {
                t = j;
            }
        }
        st[t] = true;
        for (int j = 1; j <= n; ++j) {
            dist[j] = max (dist[j], dist[t] * g[t][j]);
        }
    }
}
int main() {
    //g初始化为0，表示在没有边的情况下，i往j转账后，j得到0元钱
    cin >> n >> m;
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        double z = (100.0 - c) / 100;
        g[a][b] = g[b][a] = z;
    }
    cin >> S >> T;
    dijkstra();
    printf("%.8lf", 100.0 / dist[T]);
    return 0;
}
```

