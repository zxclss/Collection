```c++
#include <iostream>
using namespace std;

//f[i]表示前i个烽火台信息流通且点亮第i个烽火台的方案
//f[i] = min(f[i-1], f[i-2], ... , f[i-m]) + w[i]

const int N = 2e5 + 10;
int n, m;
int w[N], q[N], f[N];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);
    
    int hh = 0, tt = 0; //初始f[0] = 0入队
    for (int i = 1; i <= n; ++i) {
        if (hh <= tt && q[hh] < i - m) ++hh;
        f[i] = f[q[hh]] + w[i];
        while (hh <= tt && f[q[tt]] >= f[i]) --tt;
        q[++tt] = i;
    }
    
    int res = 1e9;
    for (int i = n - m + 1; i <= n; ++i) res = min(res, f[i]);
    printf("%d\n", res);
    
    return 0;
}
```

