> Kruskal算法的性质：每次选择边的操作是在合并两个连通块
```c++
#include <iostream>
#include <algorithm>
#include <cmath>

#define x first
#define y second

using namespace std;

// kruskal算法的另外一个数学性质
// 初始时，没有添加所有边的图中，每一个点都是孤立的 n 个连通块
// kruskal最小生成树算法，每次选择的边都是合并两个连通块
// 因此第 0 次选择到边后，图中剩余 n 个连通块
// 因此第 1 次选择到边后，图中剩余n-1个连通块
// 因此第 2 次选择到边后，图中剩余n-2个连通块
// ......
// 因此第n-1次选择到边后，图中剩余 1 个连通块（即最小生成树）
//
// 而根据这一题的题目要求，k个卫星设备，代表着我们做完选边之后，图中至多要有k个连通块
// 又根据kruskal算法的性质，每次选择的边一定是构成连通块的最小的边
// 那么这题的要求就变成了用kruskal算法求第n - k条选择的边的长度d

typedef pair<int, int> PII;

const int N = 510, M = N * N / 2;   //最小生成树都是无向边
int n, m, k;
PII pos[N];
int p[N];
struct Edge{
    int a, b;
    double w;
    bool operator< (const Edge& t) const {
        return w < t.w;
    }
}edges[M];

double get_dist(PII a, PII b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
int find(int u) {
    if (p[u] != u) p[u] = find(p[u]);
    return p[u];
}
int main() {
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> pos[i].x >> pos[i].y;
    for (int i = 0; i < n; ++i) p[i] = i;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            edges[m++] = {i, j, get_dist(pos[i], pos[j])};
    
    sort(edges, edges + m);
    
    int cnt = n;    //cnt记录当前图中连通块的数量
    double res;     //res记录最后一条连接的边的长度
    for (int i = 0; i < m; ++i) {
        if (cnt == k) break;
        int a = find(edges[i].a);
        int b = find(edges[i].b);
        if (a != b) {
            p[a] = b;
            --cnt, res = edges[i].w;
        }
    }
    printf("%.2lf\n", res);
    return 0;
}
```