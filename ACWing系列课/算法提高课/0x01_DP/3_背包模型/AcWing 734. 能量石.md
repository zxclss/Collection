这题是一道贪心 + dp的题目

先用贪心，确定最优解的集合(推公式)

考虑先吃`i`在吃`j`吸收的能量值: $e_i + e_j - l_j \times s_i$

如果先吃`j`后吃`i`吸收的能量值: $e_j + e_i - l_i \times s_j$

观察到，唯一的差异在于$-l_j\times s_i$与$-l_i\times s_j$

如果先吃`i`在吃`j`是最优解的话，必有: $-l_j \times s_i > -l_i \times s_j$

化简可得：$\frac{l_i}{s_i} > \frac{l_j}{s_j}$

因此最优解在$\frac{l_i}{s_i} > \frac{l_j}{s_j}$的集合中

对于给定的集合，进行0-1背包dp即可


$$
\begin{align}
DP闫氏分析法:\\
f(i,j)&集合：考虑前i个魔法石，所用时间恰好是j的方案\\
	  &属性：最大值\\
	  &状态转移方程：f(i,j) = max(f(i - 1, j),\space f(i - 1, j - s_i) + e_i - (j-s_i) * l_i);
\end{align}
$$

```c++
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 10010;
int T, n;
int f[N];
struct Stone{
    int s, e, l;
    bool operator< (const Stone& t) const {
        return s * t.l < l * t.s;
    }
}stones[N];

int main() {
    cin >> T;
    for (int C = 1; C <= T; ++C) {
        cin >> n;
        int m = 0;
        for (int i = 1; i <= n; ++i) {
            int s, e, l;
            cin >> s >> e >> l;
            m += s;
            stones[i] = {s, e, l};
        }
        sort(stones + 1, stones + n + 1);
        
        memset(f, -0x3f, sizeof f);
        f[0] = 0;
        for (int i = 1; i <= n; ++i) {
            auto &p = stones[i];
            for (int j = m; j >= p.s; --j) {
                f[j] = max(f[j], f[j - p.s] + p.e - (j - p.s) * p.l);
            }
        }
        int res = 0;
        for (int i = 0; i <= m; ++i) res = max(res, f[i]);
        printf("Case #%d: %d\n", C, res);
    }
    return 0;
}
```

