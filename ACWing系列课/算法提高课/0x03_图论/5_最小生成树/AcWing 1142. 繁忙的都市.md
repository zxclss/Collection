> Kruskal不但能求构成最小生成树的边的总和，还能求构成最小生成树的所有边的最大值
```c++
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

/*
kruskal算法，在计算最小生成树的时候，需要把边从小到大排序
然后主要把集合分成两种形式：
    （1）当前边所连接的两个点已经联通了，抛弃这条边
    （2）当前边所连接的两个点还未联通，选择这条边，把两个连通块合并在一起
根据这种集合的划分，我们发现了一个性质：
    当所有点联通的时候，构成这个连通块的所有边中的最大边的最小值，就是构成最小生成树的最大边

因此，本题直接使用Kruskal算法，构成最小生成树的最大边就是构成连通图方案中所有边的最大边的最小值

Kruskal不但能求构成最小生成树的边的总和，还能求构成最小生成树的所有边的最大值
*/

const int N = 310, M = 8010;
int n, m;
int p[N];
struct Edge{
    int a, b, w;
    bool operator< (const Edge& t) const {
        return w < t.w;
    }
}edges[M];

int find(int u) {
    if (p[u] != u) p[u] = find(p[u]);
    return p[u];
}
int kruskal() {
    int res = 0;
    for (int i = 0; i < m; ++i) {
        Edge &t = edges[i];
        int a = find(t.a), b = find(t.b), w = t.w;
        if (a != b) {
            p[a] = b;
            res = w;
        }
    }
    return res;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) p[i] = i;
    for (int i = 0; i < m; ++i) cin >> edges[i].a >> edges[i].b >> edges[i].w;
    sort(edges, edges + m);
    cout << n - 1 << " " << kruskal() << endl;
    return 0;
}
```