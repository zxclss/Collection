```c++
状态表示-集合f[i][j]：从0～j的路径i上的路径之和（i用二进制形式来表示经过的点）
状态表示-属性：最小值
状态计算-集合划分：
    ｜0～j的路径i上，倒数第二经过的点是k1，f[i - (1 << j)][k1]
    ｜0～j的路径i上，倒数第二经过的点是k2，f[i - (1 << j)][k2]
    ｜......
状态计算-状态转移方程：
    f[i][j] = min{f[i - (1 << j)][k1] + a[k1][j], f[i - (1 << j)][k2] + a[k2][j], ......};
```
```c++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 21, M = 1 << N;
int n;
int a[N][N];
int f[M][N];

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }
    memset(f, 0x3f, sizeof f);
    f[1][0] = 0;
    for (int i = 0; i < 1 << n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) {  //判断这个状态是否合法（第i个点在不在状态里）
                for (int k = 0; k < n; ++k) {
                    if (i >> k & 1) {  //判断k这个点在不在已遍历过的点里
                        f[i][j] = min(f[i][j], f[i - (1 << j)][k] + a[k][j]);
                    }
                }
            }
        }
    }
    cout << f[(1 << n) - 1][n - 1] << endl;
    return 0;
}
```