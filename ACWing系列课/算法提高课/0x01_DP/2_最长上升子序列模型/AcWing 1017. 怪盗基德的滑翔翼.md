```c++
#include <iostream>
using namespace std;

const int N = 110;
int T, n;
int w[N], f[N];

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);

        int res = 0;
        //假设往左边跳，就做一次最长上升子序列Dp
        for (int i = 1; i <= n; ++i) {
            f[i] = 1;
            for (int j = 1; j < i; ++j) {
                if (w[j] < w[i]) {
                    f[i] = max(f[i], f[j] + 1);
                }
            }
            res = max(res, f[i]);
        }
        //假设往右边跳，就反向做一次最长上升子序列Dp
        for (int i = n; i; --i) {
            f[i] = 1;
            for (int j = n; j > i; --j) {
                if (w[j] < w[i]) {
                    f[i] = max(f[i], f[j] + 1);
                }
            }
            res = max(res, f[i]);
        }
        printf("%d\n", res);
    }
    return 0;
}
```

