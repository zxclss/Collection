由上一题的公式继续变形
$$
\begin{align}
f[i] &= f[j] + t[i] \cdot (c[i] - c[j]) + s \cdot (c[n] - c[j]) \\
f[i] &= f[j] - (t[i] + s)\cdot c[j] + t[i]\cdot c[i] + s \cdot c[n] \\
\end{align}
$$
观察到`f[i]`是所求的值，`f[j]`和`c[j]`为两个变量，不妨设`f[j]=y, c[j]=x`

继续变形
$$
\begin{align}
f[i] &= y - (t[i]+s)x - b \\
y    &= (t[i]+s)x + f[i] + b
\end{align}
$$
观察到要使`f[i]`最小，`t[i]+s`是固定的斜率，因此就要要`y`轴截距最小即可

那么我们就要满足两个条件了：1）直线截距最小 2）直线能够经过已经计算出的状态（点）

综合以上两点，我们要求直线尽可能靠下，也就是向上平移遇到第一个点就停下

这样就可以观察到一个函数`凸包`的性质

<img src="/Users/zhaoxiucong/Library/Application Support/typora-user-images/image-20210211203509711.png" alt="image-20210211203509711" style="zoom:25%;" />

于是根据函数`凸包`的性质，我们只需找到第一个大于当前斜率的最小斜率，就是我们需要的点了（可以用二分来解决）。

但这题具有其他性质，`t[i]`随`i`增加单调上升。

因此我们就可以直接构造一个根据斜率单调递增的`单调队列`就能在队头维护我们需要的斜率了。（斜率是通过相邻点构造的）

因此在队尾插入点，就意味着`当前点`和`倒数第一个点`构成的斜率要`大于等于` `倒数第一个点`和`倒数第二个点`构成的斜率
$$
单调队列正确顺序：\frac{f_{q[tt]} - f_{q[tt-1]}}{c_{q[tt]} - c_{q[tt-1]}} \lt \frac{f_i - f_{q[tt]}}{c_i - c_{q[tt]}}
$$
然后就可以在队头维护一个斜率的最小值了，同时最小的`f[i]`就能直接通过公式确定下来了
$$
队头斜率满足要求：\dfrac{f_{q[hh+1]} - f_{q[hh]}}{c_{q[hh+1]} - c_{q[hh]}} \ge t[i]+s
$$


```c++
#include <iostream>
#include <cstring>
using namespace std;

typedef long long LL;
const int N = 3e5 + 10;
int n, s;
LL t[N], c[N];
LL f[N];
int q[N];

int main() {
    scanf("%d%d", &n, &s);
    for (int i = 1; i <= n; ++i)
        scanf("%lld%lld", &t[i], &c[i]), t[i] += t[i - 1], c[i] += c[i - 1];

    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    int hh = 0, tt = 0; //入队f[0]
    for (int i = 1; i <= n; ++i) {
        //单调队列里至少要有两个点才能构成一个斜率
        while (hh < tt && (f[q[hh + 1]] - f[q[hh]]) < (t[i] + s) * (c[q[hh + 1]] - c[q[hh]])) ++hh;
        f[i] = f[q[hh]] - (t[i] + s) * c[q[hh]] + t[i] * c[i] + s * c[n];
        while (hh < tt && (f[q[tt]] - f[q[tt - 1]]) * (c[i] - c[q[tt]]) >= (f[i] - f[q[tt]]) * (c[q[tt]] - c[q[tt - 1]])) --tt;
        q[++tt] = i;
    }
    printf("%lld\n", f[n]);
    return 0;
}
```

