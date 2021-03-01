> 最小路径点覆盖
```c++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 210, M = 30010;
int n, m;
bool st[N], f[N][N];
int match[N];

int find(int u) {
    for (int i = 1; i <= n; ++i) {
        if (f[u][i] && !st[i]) {
            st[i] = true;
            int t = match[i];
            if (t == -1 || find(t)) {
                match[i] = u;
                return true;
            }
        }
    }
    return false;
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        f[a][b] = true;
    }
    //传递闭包
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                f[i][j] |= f[i][k] & f[k][j];
            }
        }
    }
    //匈牙利算法
    int res = 0;
    memset(match, -1, sizeof match);
    for (int i = 1; i <= n; ++i) {
        memset(st, 0, sizeof st);
        if (find(i)) ++res;
    }
    cout << n - res << endl;
    return 0;
}

```
