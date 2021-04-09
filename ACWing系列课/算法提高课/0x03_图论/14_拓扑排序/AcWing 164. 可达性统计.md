> 本质是一个DP问题
> 为了能够优先计算小状态，我们采用逆拓扑序，保证计算每个状态时，其之前的状态已被计算出
> 用bitset来进行状态压缩，因为即使是ULL也不能存储下3e5个位的状态
```c++
#include <iostream>
#include <cstring>
#include <bitset>

using namespace std;

const int N = 30010;
int n, m;
int h[N], e[N], ne[N], idx;
int din[N], q[N];
bitset<N> f[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void topsort() {
    int hh = 0, tt = -1;
    for (int i = 1; i <= n; ++i)
        if (!din[i])
            q[++tt] = i;
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (--din[j] == 0) q[++tt] = j;
        }
    }
}
int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    while (m--) {
        int a, b;
        scanf("%d%d", &a, &b);
        ++din[b];
        add(a, b);
    }
    topsort();
    for (int i = n - 1; i >= 0; --i) {
        int u = q[i];
        f[u][u] = 1;    //等价于f[u] = 1 << u - 1，这这种写法这题会溢出，所以用bitset
        for (int j = h[u]; ~j; j = ne[j]) {
            int t = e[j];
            f[u] |= f[t];
        }
    }
    for (int i = 1; i <= n; ++i) printf("%d\n", f[i].count());
}

```