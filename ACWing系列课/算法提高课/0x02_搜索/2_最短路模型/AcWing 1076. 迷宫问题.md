```c++
#include <iostream>
#include <vector>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 1010, M = N * N;

int n;
int g[N][N];
bool st[N][N];
PII pre[N][N];
PII q[M];

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

void bfs(int sx, int sy) {
    int hh = 0, tt = 0;
    q[0] = {sx, sy};
    st[sx][sy] = true;

    while (hh <= tt) {
        PII t = q[hh++];
        for (int i = 0; i < 4; ++i) {
            int x = t.x + dx[i], y = t.y + dy[i];
            if (x < 0 || x >= n || y < 0 || y >= n) continue;
            if (st[x][y] || g[x][y] == 1) continue;
            st[x][y] = true;
            pre[x][y] = {t.x, t.y};
            q[++tt] = {x, y};
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &g[i][j]);
        }
    }

    bfs(0, 0);

    vector<PII> path({{n - 1, n - 1}});
    for (PII pos = {n - 1, n - 1}; pos.x || pos.y; ) {
        pos = pre[pos.x][pos.y];
        path.push_back(pos);
    }
    for (int i = path.size() - 1; i >= 0; --i)
        printf("%d %d\n", path[i].x, path[i].y);

    return 0;
}
```

