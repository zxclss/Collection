```c++
#include <iostream>
using namespace std;

/*
f[i][j]    = max(f[i-1][j], f[i-1][j-v]+w, f[i-1][j-2v]+2w, ......, f[i-1][j-sv]+sw)
f[i][j-v]  = max(           f[i-1][j-v],   f[i-1][j-2v]+1w, ......, f[i-1][j-sv]+(s-1)w, f[i-1][j-(s+1)v]+sw)
f[i][j-2v] = max(                          f[i-1][j-2v],    ......, f[i-1][j-sv]+(s-2)w, f[i-1][j-(s+1)v]+(s-1)w, f[i-1][j-(s+2)v]+sw)
f[i][j-3v] = max(                                           ......, f[i-1][j-sv]+(s-3)w, f[i-1][j-(s+1)v]+(s-2)w, f[i-1][j-(s+2)v]+(s-1)w, f[i-1][j-(s+3)v]+w)
......
f[i][j-sv] =                                                        f[i-1][j-sv],        f[i-1][j-(s+1)v]+w,      f[i-1][j-(s+2)v]+2w, ......;
......
f[i][r+3v] = max(f[i-1][r+3v],  f[i-1][r+2v]+w, f[i-1][r+v]+2w, f[i-1][r]+3w);
f[i][r+2v] = max(               f[i-1][r+2v],   f[i-1][r+v]+w,  f[i-1][r]+2w);
f[i][r+v]  = max(                               f[i-1][r+v],    f[i-1][r]+w);
f[i][r]    =                                                    f[i-1][r]
f[i][r+v]  = max(f[i-1][r+v], max(f[i][r]) + w));
f[i][r+2v] = max(f[i-1][r+2v],max(f[i][r+ v] + w));
f[i][r+2v] = max(f[i-1][r+3v],max(f[i][r+2v] + w));
......
f[i][j-sv] = max(f[i-1][j-sv], max(f[i][j-(s+1)v] + w));
......
f[i][j-2v] = max(f[i-1][j-2v], max(f[i][j-3v] + w));
f[i][j-v]  = max(f[i-1][j- v], max(f[i][j-2v] + w));
f[i][j]    = max(f[i-1][j]   , max(f[i][j- v] + w));
注意：计算滑动窗口的最大值的时候会发现，后一项比前一项多w，在比较的时候需要额外减去对应偏移量w
减去的w数量x就是相对于r差x个v

**(r = j % v, 我们这种方式相当于把所有mod v同余的情况放在一起计算)**

观察到一个滑动窗口 + 单调队列(最大值)的数据结构
滑动窗口的最大长度由物品的数量限制
滑动窗口从r枚举到m，步长是v
每次都是计算的当前滑动窗口内的最大值

*/
const int N = 1010, M = 20010;
int n, m;
int v[N], w[N], s[N];
int f[N][M];
int q[M];
//用单调队列来存储在考虑前i个物品中，体积mod v[i]同余j的方案中，使用i个物品数不超过上限的最大价值

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d%d%d", &v[i], &w[i], &s[i]);
    for (int i = 1; i <= n; ++i) {
        //j迭代的是mod v同余j的所有体积(j, j+v, j+2v, ..., j+kv)
        //从0~v-1全部迭代，覆盖到所有可能
        for (int j = 0; j < v[i]; ++j) {
            //重制单调队列q
            int hh = 0, tt = -1;
            for (int k = j; k <= m; k += v[i]) {
                //检查单调队列长度是否超过s[i]
                //算上队头元素和新加入的元素，是否物品的数量会不够用
                if (hh <= tt && q[hh] < k - s[i] * v[i]) ++hh;
                //单调递减队列，用即将加入的新元素，弹掉队尾所有比他小的元素
                while (hh <= tt && f[i-1][q[tt]] - (q[tt] - j) / v[i] * w[i] <= f[i-1][k] - (k - j) / v[i] * w[i]) --tt;
                //新元素入队
                q[++tt] = k;
                //计算答案: 队头元素作为最大值记录
                //前i-1个物品的q[hh]体积的最大价值 + 剩余体积由物品i全部填满的价值
                f[i][k] = f[i-1][q[hh]] + (k - q[hh]) / v[i] * w[i];
            }
        }
    }
    printf("%d\n", f[n][m]);
    return 0;
}
```



## 一维优化

因为每次只用到i-1层的状态，因此只需额外开一个数组来存储之前一层的状态即可

```c++
#include <iostream>
#include <cstring>
using namespace std;

const int N = 1010, M = 20010;
int n, m;
int v[N], w[N], s[N];
int f[M], pre[M], q[M];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d%d%d", &v[i], &w[i], &s[i]);
    for (int i = 1; i <= n; ++i) {
        memcpy(pre, f, sizeof f);
        for (int j = 0; j < v[i]; ++j) {
            int hh = 0, tt = -1;
            for (int k = j; k <= m; k += v[i]) {
                if (hh <= tt && q[hh] < k - s[i] * v[i]) ++hh;
                while (hh <= tt && pre[q[tt]] - (q[tt] - j) / v[i] * w[i] <= pre[k] - (k - j) / v[i] * w[i]) --tt;
                q[++tt] = k;
                f[k] = pre[q[hh]] + (k - q[hh]) / v[i] * w[i];
            }
        }
    }
    printf("%d\n", f[m]);
    return 0;
}
```

