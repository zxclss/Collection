```c++
#include <iostream>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 55, M = N * N;
int n, m;
int g[N][N];
int st[N][N];
PII q[M];

int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};

int bfs(int i, int j) {
    int hh = 0, tt = 0;
    q[0] = {i, j};
    st[i][j] = true;

    int area = 0;
    while (hh <= tt) {
        auto t = q[hh++];
        ++area;
        for (int i = 0; i < 4; ++i) {
            int x = t.x + dx[i], y = t.y + dy[i];
            if (x < 0 || x >= n || y < 0 || y >= m || st[x][y]) continue;
            if (g[t.x][t.y] >> i & 1) continue; //这里是从本体来看，有没有墙壁
            st[x][y] = true;
            q[++tt] = {x, y};
        }
    }
    return area;
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> g[i][j];
    int cnt = 0, maxArea = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (st[i][j]) continue;
            maxArea = max(maxArea, bfs(i, j));
            ++cnt;
        }
    cout << cnt << endl << maxArea << endl;
    return 0;
}
```

