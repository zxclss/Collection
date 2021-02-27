<img src="/Users/zhaoxiucong/Library/Application Support/typora-user-images/image-20210204195622905.png" alt="image-20210204195622905" style="zoom:25%;" />

```c++
#include <iostream>
#include <cstring>
using namespace std;

/*
点：
    状态0: 冷却期未持仓, 不可购入
    状态1: 未持仓, 可购入
    状态2: 持仓, 可卖出
    入口: f(0, 1) = 0
边：
    f(i, 0) = f(i-1, 2) + w[i]
    f(i, 1) = max{f(i-1, 1), f(i-1, 0)}
    f(i, 2) = max{f(i-1, 1) - w[i], f(i-1, 2)}
*/

const int N = 1e5 + 10;
int n;
int w[N];
int f[N][3];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);

    memset(f, -0x3f, sizeof f);
    for (int i = 0; i <= n; ++i) f[i][1] = 0;

    for (int i = 1; i <= n; ++i) {
        f[i][0] = f[i - 1][2] + w[i];
        f[i][1] = max(f[i - 1][1], f[i - 1][0]);
        f[i][2] = max(f[i - 1][1] - w[i], f[i - 1][2]);
    }
    cout << max(f[n][1], f[n][0]) << endl;
    return 0;
}
```

