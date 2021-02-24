```c++
#include <cstring>
#include <iostream>
using namespace std;

/*
Floyd算法的性质：
    f[i][j][k]:起点为i终点为j的一条，经过点的编号不超过k的最短路径

而这一题是让我们在一个无向图中寻找最小环，在更新第k个状态之前无向图中的环具有性质：
    i -> k -> j -> i    (j -> i 是f[i][j][k-1]的路径，而i->k与k->j的最短路径就是g[i][k]和g[k][j]，不经过其他点)
因此我们把每个环由他所有点中，编号最大的那个点来表示
那个第k个环就可以求出他的长度了 res = f[i][j][k - 1] + f[i][j][k]
*/

const int N = 110, INF = 0x3f3f3f3f;
int n, m;
int g[N][N];
int f[N][N];
int pos[N][N];
int path[N], cnt;
int res = INF;

void get_path(int l, int r) {
    int k = pos[l][r];
    if (k == 0) return;
    
    get_path(l, k);
    path[cnt++] = k;
    get_path(k, r);
}
int main() {
    memset(g, 0x3f, sizeof g);
    memset(f, 0x3f, sizeof f);
    cin >> n >> m;
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = g[b][a] = min(g[a][b], c);
    }
    memcpy(f, g, sizeof g);
    //floyd
    for (int k = 1; k <= n; ++k) {
        
        //统计答案
        for (int i = 1; i <= n; ++i) {
            //环至少要3个点组成，因此i!=j
            for (int j = i + 1; j <= n; ++j) {
                if (res > (long long)f[i][j] + g[i][k] + g[k][j]) {
                    res = f[i][j] + g[i][k] + g[k][j];
                    //把path更新成最新的
                    cnt = 0;
                    path[cnt++] = k;
                    path[cnt++] = i;
                    //i、j、k都在环的右侧，左侧是f[i][j][k - 1]的路径，用dfs来处理
                    get_path(i, j);
                    path[cnt++] = j;
                }
            }
        }
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (f[i][j] > f[i][k] + f[k][j]) {
                    f[i][j] = f[i][k] + f[k][j];
                    pos[i][j] = k;
                }
            }
        }
    }
    if (res == INF) puts("No solution.");
    else {
        for (int i = 0; i < cnt; i ++ ) cout << path[i] << ' ';
        cout << endl;
    }
    
    return 0;
}
```

