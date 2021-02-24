```c++
#include <iostream>
#include <cstring>
using namespace std;

const int N = 22;
int n, m;
char g[N][N];

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int dfs(int sx, int sy) {
    if (g[sx][sy] == '#') return 0;
    
    int res = 1;
    g[sx][sy] = '#';
    for (int i = 0; i < 4; ++i) {
        int x = sx + dx[i], y = sy + dy[i];
        if (x < 0 || x >= n || y < 0 || y >= m) continue;
        res += dfs(x, y);
    }
    return res;
}
int main() {
    while (cin >> m >> n, n || m) {
        for (int i = 0; i < n; ++i) cin >> g[i];
        int sx, sy;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (g[i][j] == '@')
                    sx = i, sy = j;
        cout << dfs(sx, sy) << endl;
    }
    return 0;
}
```

