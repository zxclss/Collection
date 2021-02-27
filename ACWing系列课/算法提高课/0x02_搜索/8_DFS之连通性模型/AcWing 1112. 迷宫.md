```c++
#include <iostream>
#include <cstring>
using namespace std;

const int N = 110;
int T, n;
char g[N][N];
bool st[N][N];
int sx, sy, ex, ey;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

bool dfs(int sx, int sy) {
    if (g[sx][sy] == '#') return false;
    if (sx == ex && sy == ey) return true;
    st[sx][sy] = true;
    for (int i = 0; i < 4; ++i) {
        int x = sx + dx[i], y = sy + dy[i];
        if (x < 0 || x >= n || y < 0 || y >= n || st[x][y]) continue;
        if (dfs(x, y)) return true;
    }
    return false;
}
int main() {
    cin >> T;
    while (T--) {
        memset(st, 0, sizeof st);
        cin >> n;
        for (int i = 0; i < n; ++i) cin >> g[i];
        // for (int i = 0; i < n; ++i) cout << g[i] << endl;
        cin >> sx >> sy >> ex >> ey;
        bool t = dfs(sx, sy);
        if (t) puts("YES");
        else puts("NO");
    }
    return 0;
}
```

