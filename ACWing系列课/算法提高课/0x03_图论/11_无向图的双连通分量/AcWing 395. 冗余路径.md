1. 边双连通分量 `e-DCC`
   `极大`的不包含`桥`的`连通块`

2. 点双连通分量 `v-DCC`
   `极大`的不包含`割点`的`连通块`
   每个`割点`至少属于`两个`连通分量，不然他被删掉后就不会构成两个连通块了

## **边双连通分量**
类似于`有向图中强连通分量`的两个数组`dfn[]`和`low[]`

> 无向图是不存在横插边的

算法模板基本和`SCC`的`tarjan算法`类似

**问题1**：如何找到桥 `x-y`
    看当前结点`y`能不能走回到`x`或`x的祖先结点`:
        如果可以的话，那就说明`x-y`这条边是在`环`中的，那必然不是`桥`；
        否则是`桥`
    `x-y`是桥 $\Leftrightarrow$ `dfn[x] < low[y]`

**问题2**：如何找到所有边的双连通分量
1.  将所有桥删掉
2.  使用`stack`，如果搜索完后`dfn[x] == low[x]`，则表示`x`后面的点无论如何都搜不到其他点了，那么当前还处于栈中的点就构成一个`边双连通分量`

对于所有的`边双连通分量`进行`缩点`，就会得到一棵`树`

如果想要把这棵`树`变成一个`边双连通分量`，则需要对所有`度数`为`1`的点加上一条边。
> 这样，当我们删去原图中的任意一个`桥`后，新图中仍然有一条我们`新添加`的边，能够使这个`点`能与其他点`连通`。相应的也就不存在桥了，于是就得到了一个边的双连通分量。

$加边数 \ge \lceil\frac{cnt}{2}\rceil = \lfloor\frac{cnt + 1}{2}\rfloor \quad ，其中cnt为度为1的点的个数$

> 至此我们可以简单总结一下：
> 把一个`有向图`合并成一个`SCC`，添加的`最少`边数为 $max\{p, q\}$, 其中`p`是`入度`为`0`的点的个数，`q`是`出度`为`0`的点的个数；
> 把一个`无向图`合并成一个`eDCC`，添加的`最少`边数为$\lfloor\frac{cnt + 1}{2}\rfloor$，其中`cnt`为`度为1`的点的个数

## Code
```c++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 5010, M = 20010;
int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
int dcc_cnt, id[N];
int deg[N];
bool is_bridge[M];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void tarjan(int u, int from) {
    dfn[u] = low[u] = ++timestamp;
    stk[++top] =u;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j, i);
            low[u] = min(low[u], low[j]);
            //如果j走不到u或u的祖先，那么他就不构成一个环，则必然是桥
            if (dfn[u] < low[j]) {
                //无向图的两条边是两两一起存储的
                //异或上1，就能找到另一条边 01-10,00-01,10-11,11-00
                is_bridge[i] = is_bridge[i ^ 1] = true;
            }
        } else if (i != (from ^ 1)) {
            //这里是判断当前的边是不是来路的反向边
            //如果既不是反向边的话，又已经被遍历过，那毫无疑问构成了一个环，回到了j
            low[u] = min(low[u], dfn[j]);
        }
    }
    if (dfn[u] == low[u]) {
        int y;
        ++dcc_cnt;
        do {
            y = stk[top--];
            id[y] = dcc_cnt;
        } while (y != u);
    }
}
int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    tarjan(1, -1);  //图是连通的，因此从1开始即可
    //无向图有两条边，我们传入一个from，记录来路的边
    
    for (int i = 0; i < idx; ++i)
        if (is_bridge[i])
            ++deg[id[e[i]]];    //只需加1边，一位正向反向边都存了，我们统一加右边
    
    //统计度为1的点
    int cnt = 0;
    for (int i = 1; i <= dcc_cnt; ++i)
        if (deg[i] == 1)
            ++cnt;
    cout << (cnt + 1) / 2 << endl;
    return 0;
}
```
