```c++
#include <iostream>
#include <cstring>
using namespace std;

/*
树形DP问题
分析结点i个集合划分（结点i到其他结点的最远距离）
    1）从i往下走到叶结点:
        down{child(i)} + w
    2）从i往上走，再从i的父结点j出发到叶结点（j此时已经更新好往上走和往下走的最大值了）:
        max{down{j + w}, up{j + w}}
        *【注】这里往上走的时候，i个父结点j再往下走的时候是不能经过i结点的(这是一条走回头路的路径，不合法)
        因此我们需要额外开一个down2[]数组才存储向下的此大值，避免down1[j]的路径是经过i的，而导致无法更新这里的值
        
    综上我们需要进行两轮的dfs：
        第一轮(自下而上)更新出每个结点向下走到叶结点的最大值及次大值，
        第二轮(从上往下)更新所有结点往上走到他的父结点，再从父结点走到叶结点的路径最大值
*/

const int N = 10010, M = 2 * N, INF = 0x3f3f3f3f;
int n;
int h[N], e[M], ne[M], w[M], idx;
int down1[N], down2[N], up[N];
int p1[N], p2[N];
//parent数组用于记录向下最大值和次大值是从那个叶结点更新上来的
//便于向上更新的时候父结点j知道最大值是否是从i更新过来的
//parent数组不用初始化，因为0是一个不存在的点，已经默认初始化好了

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}
int dfs_down(int u, int father) {
    // down1[u] = down2[u] = -INF; //这题所有边权都是正的，可以不用初始化为负无穷
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == father) continue;
        
        int dist = dfs_down(j, u) + w[i];
        if (dist >= down1[u]) {
            down2[u] = down1[u], down1[u] = dist;
            p2[u] = p1[u], p1[u] = j;
        } else if (dist > down2[u]) down2[u] = dist, p2[u] = j;
    }
    // if (down1[u] == -INF) down1[u] = down2[u] = 0; //特判叶子结点
    //把最大值返回用于更新父结点（最大值是我们向下dfs的主要目标，次大值是为了方便向上dfs不走回头路才设置的）
    return down1[u];
}
void dfs_up(int u, int father) {
    for (int i = h[u]; ~i; i = ne[i]) {
        //这里我们实际想更新的是j而不是u
        int j = e[i];
        if (j == father) continue;
        
        //如果要更新的点j，恰好在u往下走的最大路径，那就用次最大路径来更新j
        //否则就用最大值来更新就好了
        if (j == p1[u]) up[j] = max(up[u], down2[u]) + w[i];
        else up[j] = max(up[u], down1[u]) + w[i];
        
        //drill down
        dfs_up(j, u);
    }
}
int main() {
    memset(h, -1, sizeof h);
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }
    dfs_down(1, -1);
    dfs_up(1, -1);
    
    int res = INF;
    for (int i = 1; i <= n; ++i) res = min(res, max(down1[i], up[i]));
    printf("%d\n", res);
    
    return 0;
}
```

