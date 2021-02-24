```c++
#include <iostream>
using namespace std;

//字典序最小的意思就是，有编号小的物品就尽量使用他
//因此这题我们先从后往前dp出最大值，再从前往后倒推出方案即可
const int N = 1010;
int n, m;
int v[N], w[N];
int f[N][N];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> v[i] >> w[i];
    for (int i = n; i > 0; --i) {
        for (int j = m; j > 0; --j) {
            f[i][j] = f[i + 1][j];
            if (j >= v[i]) f[i][j] = max(f[i][j], f[i + 1][j - v[i]] + w[i]);
        }
    }
    // cout << f[1][m] << endl;
    for (int i = 1, j = m; i <= n; ++i) {
        if (j >= v[i] && f[i][j] - w[i] == f[i + 1][j - v[i]]) {
            cout << i << " ";
            j -= v[i];
        }
    }
    return 0;
}
```