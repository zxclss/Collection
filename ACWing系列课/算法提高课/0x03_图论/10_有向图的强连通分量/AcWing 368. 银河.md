```c++
#include <iostream>
#include <cstring>

using namespace std;

/*
这题就是“糖果”原题一模一样
这次我们来用tarjan算法求scc方法解

差分约束不再做过多介绍，这题主要针对tarjan算法的部分详述一下
差分约束后是把题目变成一个在图中求最长路的问题（上界的最小值）
    1）图中如果有正环，则无解
        上述情况对应到SCC中，我们要知道，无论正负，凡是环，就一定存在SCC内部
    因为，环一定能保证环中所有点是可以搜到环中其他点的，所以找正环的问题就变
    成了在SCC内部是否有大于0的边
        为什么这只用找大于0的边呢？
                因为图中有限制，所有的边都是非负的，具体看下边建的边
                对于都是非负的边，找一个正环，就意味着一旦环中出现了一条正边，那么
            这条正边就可以被用来无限更新长度，遂是正环
        所以我们在缩点的过程中，不同SCC的点建边，相同SCC的点判断边权，大于0直接返回false
    2）如果求最长路
        根据上面提到的，有正环则无解，因此如果有解，则所有的SCC内部的边权一定都是0
        故我们只需求缩点后的图的最长路就好了，非常的简单~~

步骤：O(n)
1、构造差分约束
2、tarjan算法求SCC
3、缩点
4、递推出最长路（tarjan保证了拓扑序，因此不需要额外的最短路算法）
*当然234步可以替换成spfa，但是时间复杂度会很高，具体方法在“糖果”这题的打卡代码中
*/
typedef long long LL;
const int N = 100010, M = 600010;
int n, m;
int h[N], hs[N], e[M], w[M], ne[M], idx;
int dfn[N], low[N], timestamp, stk[N], top;
bool in_stk[N];
int scc_cnt, id[N], scc_size[N];
LL dist[N];

void add(int h[], int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u, in_stk[u] = true;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        } else if (in_stk[j]) low[u] = min(low[u], dfn[j]);
    }
    if (low[u] == dfn[u]) {
        int y;
        ++scc_cnt;
        do {
            y = stk[top--];
            in_stk[y] = false;
            id[y] = scc_cnt;
            ++scc_size[scc_cnt];
        } while (y != u);
    }
}
int main() {
    scanf("%d%d", &n, &m);
    
    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);
    while (m--) {
        int a, b, t;
        scanf("%d%d%d", &t, &a, &b);
        if (t == 1) add(h, b, a, 0), add(h, a, b, 0);   //A>=B, B>=A
        else if (t == 2) add(h, a, b, 1);               //B>=A+1
        else if (t == 3) add(h, b, a, 0);               //A>=B
        else if (t == 4) add(h, b, a, 1);               //A>=B+1
        else add(h, a, b, 0);                           //B>=A
    }
    for (int i = 1; i <= n; ++i) add(h, 0, i, 1);       //A>=1
    tarjan(0);  //0是超级源点，所以不需要额外写一层迭代
    //缩点
    bool flag = true;
    for (int t = 0; t <= n; ++t) {
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            int a = id[t], b = id[j];
            //同一个SCC中，如果有正权边，则必然存在正环，输出无解
            if (a == b && w[i] > 0) {
                flag = false;
                break;
            } else if (a != b) add(hs, a, b, w[i]);
        }
        if (!flag) break;
    }
    //按照拓扑序递推出最长路
    if (!flag) puts("-1");
    else {
        for (int t = scc_cnt; t; --t) {
            for (int i = hs[t]; ~i; i = ne[i]) {
                int j = e[i];
                if (dist[j] < dist[t] + w[i]) {
                    dist[j] = dist[t] + w[i];
                }
            }
        }
        //统计答案
        LL res = 0;
        for (int i = 1; i <= scc_cnt; ++i) res += dist[i] * scc_size[i]; //同一个SCC中的值都相等
        printf("%lld\n", res);
    }
    return 0;
}
```