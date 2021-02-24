```c++
#include <iostream>
using namespace std;

const int N = 110;
int n;
int a[N];
int f[N], g[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    //最长上升子序列
    for (int i = 1; i <= n; ++i) {
        f[i] = 1;
        for (int j = 1; j < i; ++j) {
            if (a[j] < a[i]) {
                f[i] = max(f[i], f[j] + 1);
            }
        }
    }
    //最长下降子序列
    for (int i = n; i; --i) {
        g[i] = 1;
        for (int j = n; j > i; --j) {
            if (a[j] < a[i]) {
                g[i] = max(g[i], g[j] + 1);
            }
        }
    }
    //枚举答案
    int res = 0;
    for (int i = 1; i <= n; ++i) res = max(res, f[i] + g[i] - 1);
    printf("%d\n", n - res);
    
    return 0;
}
```

