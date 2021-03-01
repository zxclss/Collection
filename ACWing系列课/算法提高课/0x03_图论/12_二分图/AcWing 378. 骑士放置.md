> 最大独立集
```c++
#include <iostream>
#include <cstring>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;
const int N = 110;
int n, m, k;
PII match[N][N];
int g[N][N], st[N][N];

int dx[8] = {1, -1, -2, -2, -1, 1, 2, 2};
int dy[8] = {-2, -2, -1, 1, 2, 2, 1, -1};

bool find(int i, int j) {
    for (int d = 0; d < 8; ++d) {
        int x = i + dx[d], y = j + dy[d];
        if (x <= 0 || x > n || y <= 0 || y > m) continue;
        if (g[x][y] || st[x][y]) continue;
        st[x][y] = true;
        
        PII t = match[x][y];
        if (t.x == 0 || find(t.x, t.y)) {
            match[x][y] = {i, j};
            return true;
        }
    }
    return false;
}
int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < k; ++i) {
        int a, b;
        cin >> a >> b;
        g[a][b] = true;
    }
    
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (g[i][j] || (i + j) & 1) continue;
            memset(st, 0, sizeof st);
            if (find(i, j)) ++res;
        }
    }
    cout << n * m - k - res << endl;
    return 0;
}
```