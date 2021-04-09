> 欧拉路径
```c++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 510, M = 1100;
int n = 500, m;
int g[N][N];
int d[N];
int path[M], cnt;

void dfs(int u) {
    for (int i = 1; i <= n; ++i) {
        if (g[u][i]) {s
            --g[u][i], --g[i][u];
            dfs(i);
        }
    }
    path[++cnt] = u;
}
int main() {
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        ++g[a][b], ++g[b][a];
        ++d[a], ++d[b];
    }
    //起点要么度数为奇数；要么就是所有点的度数为偶数，任意存在的点作为起点
    int start = 1;
    while (!d[start]) ++start;
    for (int i = 1; i <= n; ++i) {
        if (d[i] & 1) {
            start = i;
            break;
        }
    }
    dfs(start);
    for (int i = cnt; i; --i) cout << path[i] << endl;
    return 0;
}
```