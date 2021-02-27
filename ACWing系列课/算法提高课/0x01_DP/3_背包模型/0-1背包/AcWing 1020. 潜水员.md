```c++
#include <iostream>
#include <cstring>
using namespace std;

//f[i][j][k]状态表示:
//      集合: 考虑前i个物品，体积1至少是j，体积2至少是k的方案
//      属性: Min
//状态计算：
//      集合划分: 选第i个物品和不选第i个物品
//      f[i][j][k] = min(f[i-1][j][k], f[i-1][j-v1][k-v2]);
//注: 这里j-v1和k-v2和导致数组越界，但是实际意义是体积1和体积2至少是j-v1和k-v2，即使是负数他们也是有实际意义的
//因此这里把这里至少是负体积的情况全部由0进行集合的划分
//即  max(0,j-v1)  与  max(0,k-v2)

const int N = 25, M = 80;
int n, m, K;
int f[N][M];

int main() {
    memset(f, 0x3f, sizeof f);
    f[0][0] = 0;
    
    scanf("%d%d%d", &n, &m, &K);
    for (int i = 1; i <= K; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        for (int j = n; j >= 0; --j) {
            for (int k = m; k >= 0; --k) {
                f[j][k] = min(f[j][k], f[max(0, j - a)][max(0, k - b)] + w);
            }
        }
    }
    printf("%d\n", f[n][m]);
    return 0;
}
```

