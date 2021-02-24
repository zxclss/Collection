> 披着图论问题的Floyd问题的dp问题的快速幂优化问题
```
floyd：	f[k][i][j]:表示从i到j，经过编号在1～k内的点的最短路
本题：	   f[k][i][j]:表示从i到j，经过k条边的最短路
状态计算：f[a+b][i][j] = f[a][i][k] + f[b][k][j]
            f[k][i][j] = (f[1][i][k1] + f[1][k1][k2]) + ... + (f[1][kn-1][kn] + f[1][kn][j])
                       =         f[2][i][o1] + ....................... + f[2][om-1][om]
                       =                             f[k][i][j]
观察到一个“结合率”的性质
“结合律”立即推 -> “快速幂”
```
```c++
#include <iostream>
#include <cstring>
#include <map>

using namespace std;

const int N = 110;
int n, k, m, S, T;
int g[N][N];
int f[N][N];

void mul(int c[][N], int a[][N], int b[][N]) {
    static int temp[N][N];
    memset(temp, 0x3f, sizeof temp);
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                temp[i][j] = min(temp[i][j], a[i][k] + b[k][j]);
            }
        }
    }
    memcpy(c, temp, sizeof temp);
}
int qmi() {
    memset(f, 0x3f, sizeof f);
    for (int i = 1; i <= n; ++i) f[i][i] = 0; //f[0][i][i] = 0
    while (k) {
        if (k & 1) mul(f, f, g);    //f = f * g
        mul(g, g, g);   //g = g * g
        k >>= 1;
    }
}
int main() {
    memset(g, 0x3f, sizeof g);
    cin >> k >> m >> S >> T;
    map<int, int> hash;
    while (m--) {
        int a, b, c;
        cin >> c >> a >> b;
        if (!hash.count(a)) hash[a] = ++n;
        if (!hash.count(b)) hash[b] = ++n;
        int x = hash[a], y = hash[b];
        g[x][y] = g[y][x] = min(g[x][y], c);
    }
    S = hash[S], T = hash[T];
    qmi();
    cout << f[S][T] << endl;
    
    return 0;
}
```