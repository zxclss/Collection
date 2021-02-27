

```C++
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int N = 110;
typedef pair<int, int> PII;
int g[N][N];
int d[N][N];
int n, m;

int bfs() {
    memset(d, -1, sizeof d);//没有遍历过的结点，到(0, 0)点的距离设为-1。用-1来代替bool st[N]的作用。
    queue<PII> q;
    int dx[] = {1, 0, -1, 0}, dy[] = {0, -1, 0, 1};
    d[0][0] = 0;
    q.push({0, 0});
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int x = t.first + dx[i], y = t.second + dy[i];
            if (x >= 0 && x < n && y >= 0 && y < m && d[x][y] == -1 && g[x][y] != 1) {
                d[x][y] = 1 + d[t.first][t.second];
                q.push({x, y});
            }
        }
    }
    return d[n - 1][m - 1];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &g[i][j]);
        }
    }
    cout << bfs() << endl;
    return 0;
}
```

