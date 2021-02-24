```c++
#include <iostream>

#define x first
#define y second

using namespace std;

typedef pair<int,int> PII;

const int N = 1010;
int n;
int g[N][N];
bool st[N][N];
PII q[N * N];

void bfs(int i, int j, bool &higher, bool &lower) {
    int hh = 0, tt = 0;
    q[0] = {i, j};
    st[i][j] = true;

    while (hh <= tt) {
        auto t = q[hh++];
        for (int x = t.x - 1; x <= t.x + 1; ++x) {
            for (int y = t.y - 1; y <= t.y + 1; ++y) {
                if (x < 0 || x >= n || y < 0 || y >= n) continue;
                //判断边界
                if (g[x][y] !=  g[t.x][t.y]) {
                    if (g[x][y] > g[t.x][t.y]) higher = true;
                    if (g[x][y] < g[t.x][t.y]) lower = true;
                } else {
                    if (st[x][y]) continue;
                    st[x][y] = true;
                    q[++tt] = {x, y};
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%d", &g[i][j]);
    int peak = 0, valley = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (st[i][j]) continue;
            bool higher = false, lower = false;
            bfs(i, j, higher, lower);
            if (!higher) ++peak;
            if (!lower) ++valley;
        }
    }
    printf("%d %d\n", peak, valley);
    return 0;
}
```

