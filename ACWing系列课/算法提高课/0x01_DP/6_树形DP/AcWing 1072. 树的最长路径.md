```c++
#include <iostream>
#include <cstring>
using namespace std;

/*
因为存在负权边，所以不能用x-u-v的方法快速求出直径
这是一道树形DP的问题，我们需要把所有路径算出来，求一个最大值，那就是树的直径了
一条路径经过一个结点，只有两种情况：
    1）以这个结点为上升点：连在这个结点上，然后再继续往上连的路径
    2）以这个结点为拐弯点：路径从他的一个子结点连到它身上，然后拐弯再连到它的另一个子结点上
根据上述的两种情况，递归处理树的所有结点即可
*/

const int N = 10010, M = 2 * N;
int n;
int h[N], e[M], ne[M], w[M], idx;
int ans;

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
int dfs(int u, int father) {
    int dist = 0;
    //dist是存储的是以当前结点作为上升点的路径中，从当前结点的某一个叶结点上升到当前结点的最长路径
    int d1 = 0, d2 = 0; //用于存储以当前结点为拐弯点的路径长度
    //d1存储最长叶结点路径，d2存储次长叶结点路径
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == father) continue;
        int d = dfs(j, u) + w[i];
        
        dist = max(dist, d);
        if (d >= d1) d2 = d1, d1 = d;
        else if (d > d2) d2 = d;
    }
    //因为作为以当前结点作为拐弯点的路径长度是已经确定了的
    //因此可以直接更新全局ans答案
    ans = max(ans, d1 + d2);
    //对于当前结点的上升路径长度，把他传递给父结点即可
    //让父结点更新他的拐弯点路径和上升点路径
    return dist;
}
int main() {
    memset(h, -1, sizeof h);
    
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }
    
    //因为存的是无向边，因此递归每个结点的时候，可能会再次递归他的父结点
    //因此我们在dfs中额外传入一个参数father，来确保不会回去，造成死循环（也可以额外开一个数组记录每个点的遍历情况）
    dfs(1, -1); //根结点没有父结点，随便传入一个非结点编号即可
    printf("%d\n", ans);
    
    return 0;
}
```

