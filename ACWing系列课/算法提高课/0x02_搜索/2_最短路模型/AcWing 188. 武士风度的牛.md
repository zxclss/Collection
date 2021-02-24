```c++
#include <iostream>
#include <cstring>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 155, M = N * N;
int n, m;
char g[N][N];
PII q[M];
int dist[N][N];

int dx[] = {-1, 1, -2, -2, 1, -1, 2, 2};
int dy[] = {-2, -2, -1, 1, 2, 2, 1, -1};

int bfs(int sx, int sy) {
    int hh = 0, tt = 0;
    q[0] = {sx, sy};

    memset(dist, -1, sizeof dist);
    dist[sx][sy] = 0;

    while (hh <= tt) {
        PII t = q[hh++];
        for (int i = 0; i < 8; ++i) {
            int x = t.x + dx[i], y = t.y + dy[i];
            if (x < 0 || x >= n || y < 0 || y >=m) continue;
            if (dist[x][y] != -1 || g[x][y] == '*') continue;
            if (g[x][y] == 'H') return dist[t.x][t.y] + 1;
            dist[x][y] = dist[t.x][t.y] + 1;
            q[++tt] = {x, y};
        }
    }
    return -1;
}

int main() {
    cin >> m >> n;
    for (int i = 0; i < n; ++i) cin >> g[i];
    int sx, sy;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (g[i][j] == 'K') {
                sx = i, sy = j;
                break;
            }
    int t = bfs(sx, sy);
    cout << t << endl;
    return 0;
}
```

