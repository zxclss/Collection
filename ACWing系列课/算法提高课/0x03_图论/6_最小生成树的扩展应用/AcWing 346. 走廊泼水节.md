> 在不改变最小生成树的情况下，组建完全图的方法
```c++
#include <iostream>
#include <algorithm>

using namespace std;

/*
考虑在"不包含已给的最小生成树的边"，合并两个连通块组成一个完全图的过程
    题目要求连了新边以后，最小生成树仍然是原来的那棵
    因此对于这两个连通块合并的过程，所有相连的边的权值都必须大于那条已给的边
    证明：(反证法)
        假设在这两个连通块之间的任意两点x2,y2之间连取一条长度小于等于已给的x1-y1边
        那么会出现一个环：-x2-x1-y1-y2- 
        由于 x2-y2 <= x1-y1，因此在生成最小生成树的时候，这个环中，可以删去的边就是x1-y1而不是x2-y2
        这就使得最小生成树发生了变化，与题目矛盾
    因此我们在给"除给定边以外的"其他点连边的时候，边权必须严格大于给定边
    由于边必须为正数，所以边权取为 "给定边长度 + 1"

合并顺序要找Kruskal算法合并连通块的顺序
因为Kruskal算法保证了选择的边一定存在于最小生成树中，方便枚举

*/

const int N = 6010;
int T, n;
int p[N];
struct Edge{
    int a, b, w;
    bool operator< (const Edge& t) const {
        return w < t.w;
    }
}edges[N];
int cnt[N]; //统计当前连通块内点的数量(存储在根节点上)

int find(int u) {
    if (p[u] != u) p[u] = find(p[u]);
    return p[u];
}
int main() {
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; ++i) p[i] = i, cnt[i] = 1;
        for (int i = 0; i < n - 1; ++i) cin >> edges[i].a >> edges[i].b >> edges[i].w;
        sort(edges, edges + n - 1);
        
        int res = 0;
        for (int i = 0; i < n - 1; ++i) {
            int a = find(edges[i].a);
            int b = find(edges[i].b);
            int w = edges[i].w;
            if (a != b) {
                res += (cnt[a] * cnt[b] - 1) * (w + 1); //减去的 1 是最小生成树的边
                cnt[b] += cnt[a];
                p[a] = b;
            }
        }
        cout << res << endl;
    }
    return 0;
}

```