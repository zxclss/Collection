## **点双连通分量**
类似于`有向图中强连通分量`的两个数组`dfn[]`和`low[]`

**问题1**：如何求`割点`
首先必须满足 $low[y] \ge dfn[x]$
然后判断
    1. 如果 $x$ 不是`根节点`，那么 $x$ 是`割点`（此时y不能走出了`y-x`的路径到达`x`的祖先结点）
    2. $x$ 是`根节点`，至少有`第两个`子节点 $y_2$ 满足 $low[y_2] \ge dfn[x]$

**问题2**：如何求`点双连通分量`
利用`栈`来完成存储
找到`割点`后，把`栈`中所有元素连同`割点`一起存储为一个`点双连通分量`

**如何缩点**：
1.  每个割点单独作为一个点
2.  从每个V-DCC想其所包含的每个割点连边

------------------------

## AcWing 1183. 电力

本题做法：
1.  统计连通块个数 $cnt$
2.  枚举删除哪个割点后，连通块数量增加的最多
   

### Code
```c++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 10010, M = 30010;
int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int root, ans;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    int cnt = 0;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
            //j到不了u和u的祖先结点，所以u是割点，删去u会增加连通块个数
            if (low[j] >= dfn[u]) ++cnt;
        } else low[u] = min(low[u], dfn[j]);
    }
    if (u != root) ++cnt;   //u不是根节点的话，出了自己的子树，还有他的父节点也成为了独立连通块
    
    ans = max(ans, cnt);
}
int main() {
    while (scanf("%d%d", &n, &m), n || m) {
        memset(dfn, 0, sizeof dfn);
        memset(h, -1, sizeof h);
        idx = timestamp = ans = 0;
        
        while (m--) {
            int a, b;
            scanf("%d%d", &a, &b);
            add(a, b), add(b, a);
        }
        int cnt = 0;    //统计当前有多少连通块
        for (root = 0; root < n; ++root)
            if (!dfn[root]) {
                ++cnt;
                tarjan(root);
            }
        printf("%d\n", ans + cnt - 1);
    }
    return 0;
}
```