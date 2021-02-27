本题的大意是给定一个 $8 * 8$ 的棋盘，对这个棋盘进行 $n - 1(1<n<15)$ 次划分，要求每次划分后，只可以选择两块子矩阵的其中一块继续划分。

<img src="https://www.acwing.com/media/article/image/2019/02/05/19_32dad08629-1191_1.jpg" alt="1191_1.jpg"  />

完成划分后，一共会得到 $n$ 块棋盘。

原棋盘上每一格有一个分值，一块矩形棋盘的总分为其所含各格分值之和。

现在需要把棋盘按上述规则分割成 $n$ 块矩形棋盘，并使各矩形棋盘总分的均方差最小。

显然可以观察到一个二维 $区间DP$ 的模型 ~~（不对，二维是不是应该叫面积DP(滑稽)）~~

-----------------------------------

根据题意，我们可以得到的信息是

​	1)一共可以对棋盘进行 $n-1$ 次划分得到 $n$ 个子棋盘

​	2)对所有的子棋盘可以求得的平均数 $\overline{x} = \dfrac{\sum_{i=1}^nx^i}{n}$

​	3)要求总分的均方差最小 $\sigma = \sqrt{\dfrac{\sum_{i=1}^n(x_i - \overline{x})^2}{n}}$

-------------

为了使方差 $\sigma$ 最小，因此我们首先需要对 $\sigma$ 的表达式进行化简

推导过程：

​	$\sigma^2 = \frac{1}{n}(\sum_{i=1}^nx_i^2 - 2\sum_{i=1}^nx_i\cdot\overline{x} + \sum_{i=1}^n\overline{x}^2)$

​	$\sigma^2 = \frac{1}{n}\sum_{i=1}^nx_i^2 - 2\overline{x}\frac{1}{n}\sum_{i=1}^nx_i + \frac{1}{n}\cdot n\overline{x}^2$

​	$\sigma^2 = \frac{1}{n}\sum_{i=1}^nx_i^2 - 2\overline{x}^2 + \overline{x}^2$

​	$\sigma^2 = \frac{1}{n}\sum_{i=1}^nx_i^2 - \overline{x}^2$

由于 $\overline{x}$ 是常数，因此**显然**可以观察到 $\sigma$ 与 $x_i$ 是同增的

为了最终方差是最小值，我们需要满足`子矩阵的值的平方`最小

> 我们会在代码中的get()方法里实现



-----------------

`f[x1][y1][x2][y2][k]状态表示：`

`1）	集合：`划分到$k-1$个的子矩阵，是以$(x1, y1)$为左上角，$(x2,y2)$为右下角

`2）	属性：`$\sigma = \sqrt{\dfrac{\sum_{i=1}^n(x_i - \overline{x})^2}{n}}$最小值 *Min*

`状态计算：`
`1）集合划分：`

```c++
/*
    1.1) 横着切:
    	1.1.1)以(x1, y1)为左上角，以(x1, y2)为右下角 或 以(x1+1, y1)为左上角，以(x2, y2)为右下角
    	1.1.2)以(x1, y1)为左上角，以(x1+1, y2)为右下角 或 以(x1+2, y1)为左上角，以(x2, y2)为右下角
    			......
    	1.1.i)以(x1, y1)为左上角，以(x1+i, y2)为右下角 或 以(x1+i+1, y1)为左上角，以(x2, y2)为右下角
    			......
        1.1.x2-1)以(x1, y1)为左上角，以(x2-1, y2)为右下角 或 以(x2, y1)为左上角，以(x2, y2)为右下角

    1.2) 竖着切:
    	1.2.1)以(x1,y1)为左上角，以(x2, y1)为右下角 或 以(x1, y1)为左上角，以(x2, y2)为右下角
    	1.2.2)以(x1,y1)为左上角，以(x2, y1+1)为右下角 或 以(x1, y1+2)为左上角，以(x2, y2)为右下角
       			......
    	1.2.i)以(x1,y1)为左上角，以(x2, y1+i)为右下角 或 以(x1, y1+i+1)为左上角，以(x2, y2)为右下角
    			......
    	1.2.y2-1)以(x1, y1)为左上角，以(x2, y2-1)为右下角 或 以(x1,y2-1)为左上角，以(x2, y2)为右下角
*/
```

`2）状态转移方程：	`

> 模拟上述集合的划分枚举所有的区间即可
>
> 由于dp的方程维数过大，写 $5$ 重迭代太麻烦了，这题采用记忆化搜索

------------

# Code
```c++
#include <iostream>
#include <cmath>
using namespace std;

const int N = 9, M = 15;
const double INF = 1e9;

int n, m = 8;
int s[N][N];
double f[N][N][N][N][M];
double X;   //均值x拔

double get(int x1, int y1, int x2, int y2) {
    //根号下，求和符号内的部分
    double sum = s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1] - X;
    //还要平方
    return (double)sum * sum;
}
double dp(int x1, int y1, int x2, int y2, int k) {
    auto &t = f[x1][y1][x2][y2][k];
    if (t) return t;
    if (k == 1) return get(x1, y1, x2, y2);
    
    t = INF; //求最小值要初始化成最大值
    //横着切
    for (int i = x1; i < x2; ++i) {
        t = min(t, dp(x1, y1, i, y2, k - 1) + get(i + 1, y1, x2, y2));
        t = min(t, dp(i + 1, y1, x2, y2, k - 1) + get(x1, y1, i, y2));
    }
    //竖着切
    for (int i = y1; i < y2; ++i) {
        t = min(t, dp(x1, y1, x2, i, k - 1) + get(x1, i + 1, x2, y2));
        t = min(t, dp(x1, i + 1, x2, y2, k - 1) + get(x1, y1, x2, i));
    }
    return t;
}

int main() {
    cin >> n;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> s[i][j];
            s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
        }
    }
    X = (double) s[m][m] / n;
    //这个就是\sigma的完整计算公式
    printf("%.3lf\n", sqrt(dp(1, 1, m, m, n) / n));
    return 0;
}
```

