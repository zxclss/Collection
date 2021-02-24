```c++
#include <iostream>
using namespace std;

#define x first
#define y second

typedef pair<int,int> PII;
const int N = 1010;
int n, m;
char g[N][N];
bool st[N][N];
PII q[N * N];

void bfs(int i, int j) {
    int hh = 0, tt = 0;
    q[0] = {i, j};
    st[i][j] = true;
    while (hh <= tt) {
        auto t = q[hh];
        ++hh;

        for (int x = t.x - 1; x <= t.x + 1; ++x) {
            for (int y = t.y - 1; y <= t.y + 1; ++y) {
                if (x < 0 || x >= n || y < 0 || y >= m || st[x][y]) continue;
                if (g[x][y] == '.') continue;
                st[x][y] = true;
                q[++tt] = {x, y};
            }
        }
    }
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> g[i];

    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (g[i][j] == 'W' && !st[i][j]) {
                bfs(i, j);
                ++cnt;
            }
        }
    }
    cout << cnt << endl;
    return 0;
}
```

