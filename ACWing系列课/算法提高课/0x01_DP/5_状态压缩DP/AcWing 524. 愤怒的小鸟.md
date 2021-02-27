这题的大致意思就是用**尽可能少**的一条过原点，且开口朝下的抛物线，去穿过所有的点。

根据题意我们大致可以得出一下信息，对于抛物线 $y = ax^2 + bx + c$有：

1）过原点，因此$c=0$

2）开口朝下，因此$a < 0$

于是我们得到一个化简过后的方程: $y = ax^2 + bx$

--------------

又因为这题要求使用的抛物线尽可能少，所以我们需要**抛物线**能够穿过两个点$(x_1,y_1)$和$(x_2, y_2)$

于是得到方程组${\begin{cases} y_1 = ax_1^2 + bx_1 \\ y_2 = ax_2^2 + bx_2\end{cases}}$

通过反复代入消元可以得到${\begin{cases} a = \dfrac{\dfrac{y_1}{x_1} - \dfrac{y_2}{x_2}}{x_1 - x_2}\\ b = \dfrac{y_1}{x_1} - ax_1\end{cases}}$且$a < 0$

于是我们可以根据任意两个点，获得一个包含最优解的抛物线了

【注】这里有一个特殊情况，当$x_1 = x_2$的时候，是不存在这样一个能够同时穿过这两个点的抛物线的

--------------------------

最后就是状态压缩DP了

我们对于通过上述方程所得到的直线，它能够穿过的所有点，作为它的状态

而我们的目标，就是搜索所有的直线，满足在最少利用的情况下，达成$\begin{matrix} \underbrace{1111....1111} \\ n\end{matrix}$的状态

`f[i]`状态表示：

​	`集合`：当前选择的抛物线们，能够穿过的点的状态为`i`的所有方案

​	`属性`：最小值Min

`f[i]`状态计算：

​	对于当前未穿过的点`t`，枚举所有能够穿过`t`的直线`path[t][j]`

​		`f[i | path[t][j]] = min(f[i | path[t][j], f[i] + 1]);`

​	这里最差的情况是用一条单独的抛物线经过点`t`，所以比较的是`f[i] + 1`



```c++
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

#define x first
#define y second

typedef pair<double, double> PDD;

const int N = 20, M = 1 << 18;
const double eps = 1e-6;

int T, n, m;
PDD q[N];
int f[M];
int path[N][N];
//path存储的是直线
//物理层面上看，存储的是这条直线所经过的点(状态)

int gt_lf(double x, double y) {
    if (fabs(x - y) < eps) return 0;
    if (x < y) return -1;
    return 1;
}
int main() {
    cin >> T;
    while (T--) {
        memset(path, 0, sizeof path);
        cin >> n >> m;
        for (int i = 0; i < n; ++i) cin >> q[i].x >> q[i].y;
        
        //构造每两个点之间的抛物线
        for (int i = 0; i < n; ++i) {
            //并不是所有的点都能够成对出现在抛物线上的
            //会存在独立的点没能凑上对
            //因此规定每个点有一条只经过自己的抛物线
            path[i][i] = 1 << i;
            for (int j = 0; j < n; ++j) {
                double x1 = q[i].x, y1 = q[i].y;
                double x2 = q[j].x, y2 = q[j].y;
                if (!gt_lf(x1, x2)) continue;
                double a = (y1 / x1 - y2 / x2) / (x1 - x2);
                double b =  y1 / x1 - a * x1;
                if (gt_lf(a, 0) >= 0) continue;
                //查询这条过i和j的直线还经过哪些点，用状态把它存下来
                int state = 0;
                for (int k = 0; k < n; ++k) {
                    double x = q[k].x, y = q[k].y;
                    if (!gt_lf(a * x * x + b * x, y))
                        state += 1 << k;
                }
                path[i][j] = state;
            }
        }
        
        //dp
        memset(f, 0x3f, sizeof f); //求最小值的属性时，要把矩阵初始化为正无穷
        f[0] = 0; //入口，0状态不需要直线覆盖
        //这里循环到全是1的情况就好了
        for (int i = 0; i + 1 < 1 << n; ++i) {
            //找到一个当前还没有覆盖的点
            int t = 0;
            for (int j = 0; j < n; ++j)
                if (!(i >> j & 1)) {
                    t = j;
                    break;
                }
            //枚举所有能覆盖这个点的抛物线，并更新状态最小值
            for (int j = 0; j < n; ++j)
                f[i | path[t][j]] = min(f[i | path[t][j]], f[i] + 1);
        }
        cout << f[(1 << n) - 1] << endl;
    }
    return 0;
}
```

