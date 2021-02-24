```c++
#include <iostream>
using namespace std;

/*
f[i]: 对于前i头牛，选择的方案
集合划分：
    不选第i头牛：f[i-1]
    选第i头牛：1）从i开始往前连续选择1的区间长度：f[i-2] + s[i] - s[i-1]
               2）从i开始往前连续选择2的区间长度：f[i-3] + s[i] - s[i-2]
               ...
             m-1）从i开始往前连续选择m-1的区间长度：f[i-m] + s[i] - s[i-m+1]
             化简：f[i] = max{f[i-j-1] - s[i-j]} + s[i]
*/

typedef long long LL;
const int N = 1e5 + 10;
int n, m;
LL s[N];
LL f[N];
int q[N];

LL g(int t) {
    return f[t- 1] - s[t];
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%lld", &s[i]), s[i] += s[i - 1];
    
    int hh = 0, tt = 0; //f[0] = 0 入队
    for (int i = 1; i <= n; ++i) {
        if (q[hh] < i - m) ++hh;
        f[i] = max(f[i - 1], g(q[hh]) + s[i]);
        while (hh <= tt && g(q[tt]) <= g(i)) --tt;
        q[++tt] = i;
    }
    printf("%lld\n", f[n]);  
    return 0;
}

```

