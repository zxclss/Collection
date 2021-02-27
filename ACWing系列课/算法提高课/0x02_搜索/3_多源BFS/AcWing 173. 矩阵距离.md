```c++
#include <iostream>
#include <cstring>

#define x first
#define y second

using namespace std;

/*
多起点的问题（非多源汇最短路问题）的处理方式是：
    通过建立一个虚拟起点，从虚拟起点出发，往实际的多个起点分别建立一条边
    该边的边权是0，从而转换为单源最短路问题
*/

typedef pair<int,int> PII;

const int N = 1010, M = N * N;

int n, m;
char g[N][N];
int dist[N][N];
PII q[M];

void bfs() {
    memset(dist, -1, sizeof dist);
    //更新所有起点，并入队
    int hh = 0, tt = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (g[i][j] == '1') {
                dist[i][j] = 0;
                q[++tt] = {i, j};
            }
        }
    }
    
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, -1, 0, 1};
    
    while (hh <= tt) {
        PII t = q[hh++];
        for (int i = 0; i < 4; ++i) {
            int x = t.x + dx[i], y = t.y + dy[i];
            if (x < 0 || x >= n || y < 0 || y >= m) continue;
            if (dist[x][y] != -1) continue;
            dist[x][y] = dist[t.x][t.y] + 1;
            q[++tt] = {x, y};
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) scanf("%s", g[i]);
    bfs();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d ", dist[i][j]);
        }
        puts("");
    }
    return 0;
}
```

