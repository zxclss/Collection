```c++
#include <iostream>
#include <cstring>

#define x first
#define y second

using namespace std;

const int N = 10;

int T, n, m, sx, sy;
int res;
bool st[N][N];

int dx[] = {-2, -2, -1, 1, 2, 2, 1, -1};
int dy[] = {-1, 1, 2, 2, 1, -1, -2, -2};

void dfs(int u, int x, int y) {
    if (u == n * m) {
        ++res;
        return;
    }
    for (int i = 0; i < 8; ++i) {
        int a = x + dx[i], b = y + dy[i];
        if (a < 0 || a >= n || b < 0 || b >= m || st[a][b]) continue;
        st[x][y] = true;
        dfs(u + 1, a, b);
        st[x][y] = false;
    }
}
int main() {
    cin >> T;
    while (T--) {
        memset(st, 0, sizeof st);
        res = 0;

        cin >> n >> m >> sx >> sy;
        st[sx][sy] = true;
        dfs(1, sx, sy);

        cout << res << endl;
    }
    return 0;
}
```

