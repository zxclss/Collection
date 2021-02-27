## **差分约束**
### 一、 **求不等式组的可行解**

**！！！源点需要满足的条件：从`源点`出发，一定可以走到所有的边。！！！**

**步骤**：
1.  先将每个不等式 $x_i \le x_j + c_k$，转化成一条从 $x_j$ 走到 $x_i$，长度为 $c_k$ 的边。
2.  找到一个`超级源点`，使得该源点一定可以`遍历到所有边`
3.  从源点求一遍`单源最短路`

**结果1**：如果`存在负环`，则原不等式组`一定无解`
**结果2**：如果`没有负环`，则 $dist[i]$ 就是原不等式组的一个`可行解`

-----------------

### 二、 **如何求最大值或者最小值**，这里的最值指的是每个变量的最值
**结论**：如果求的是`最小值`，则应该求`最长路`；如果求的是`最大值`，则应该求`最短路`。

**问题**：如何转化 $x_i \le c$，其中 $c$ 是一个常数，这类的不等式。

**方法**：建立一个超级源点`0`，然后建立 `0 -> i` 的边，长度是 $c$ 即可。

**以求 $x_i$ 的`最大值`为例：**

求所有从 $x_i$ 出发，构成的多个形如如下的`不等式链`
$$
x_i \le x_j +c_1 \le x_k + c_2 + c_1 \le ··· \le x_0 + c_1 + c_2 + ··· + c_m    \qquad(x_0 = 0)
$$
所计算出的`上界`，最终 $x_i$ 的最大值等于`所有上界的最小值`。
这里所有`上界的最小值`可以理解这么一个例子：$\begin{cases} x_1 \le 5 \\ x_1 \le 7 \\ x_1 \le 9 \end{cases}$ ，则 $x_1$ 的最大值为 $5$

把上述转换成`图论`的问题，就是求 $dist[i]$ 的`最小值`，即`最短路`求解

**求 $x_i$ 的`最大值`** 时则完全相反，求一个形如如下`不等式链`所计算出的`下界`，最终在所有下界里取`最大值`
$$
x_i \ge x_j +c_1 \ge x_k + c_2 + c_1 \ge ··· \ge x_0 + c_1 + c_2 + ··· + c_m    \qquad(x_0 = 0)
$$
转换成`图论`的问题，就是求 $dist[i]$ 的`最大值`，即`最长路`求解

----------------

## AcWing 1169. 糖果
## 代码：

```c++
#include <iostream>
#include <cstring>

typedef long long LL;
const int N = 1e5 + 10, M = 3 * N;
int n, m;
int h[N], e[M], w[M], ne[M], idx;
int dist[N], cnt[N], q[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
bool spfa() {
    //因为是求所有x_i的最小值，因此就是求不等式的下界的最大值
    //转而就是求图论的最长路
    int hh = 0, tt = 1;
    memset(dist, -0x3f, sizeof dist);
    dist[0] = 0;
    q[0] = 0;
    
    //建立一个能够到所有点的虚拟源点0
    for (int i = 1; i <= n; ++i) add(0, i, 1);  //x_0 <= x_i + 1
    
    //这题在判负环的时候会TLE
    //上一次的“负环”题目中的trick方法还是太玄学了
    //这里用一个不会TLE的判负环方法，那就是把SPFA算法中的循环队列改为栈
    //这样对于遇到的负环，就不会加入队尾，知道再次遍历完整个队列才去算他
    //遇到负环会直接在栈顶连续入栈出栈，直到判断他的cnt[i] >= n+1，即发现负环
    while (hh != tt) {
        int t = q[--tt];
        st[t] = false;
        
        for(int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] < dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                
                if (cnt[j] >= n + 1) return true;
                
                if (!st[j]) {
                    st[j] = true;
                    q[tt++] = j;
                }
            }
        }
    }
    return false;
}
int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    while (m--) {
        int x, a, b;
        scanf("%d%d%d", &x, &a, &b);
        if (x == 1) add(a, b, 0), add(b, a, 0);
        else if (x == 2) add(a, b, 1);
        else if (x == 3) add(b, a, 0);
        else if (x == 4) add(b, a, 1);
        else if (x == 5) add(a, b, 0);
    }
    if (spfa()) puts("-1");
    else {
        LL res = 0;
        for (int i = 1; i <= n; ++i) res += dist[i];
        printf("%lld\n", res);
    }
    return 0;
}
```