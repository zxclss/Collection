> 用LCA优化后的求次小生成树
```c++
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10, M = 3e5 + 10, INF = 0x3f3f3f3f;
int n, m;
struct Edge{
    int a, b, c;
    bool tr;
    bool operator< (const Edge& t) {
        return c < t.c;
    }
}edge[M];
int h[N], e[M], w[M], ne[M], idx;
int p[N];
int depth[N], fa[N][17], d1[N][17], d2[N][17];
int q[N];

void add(int a, int b, int c) {
    e[idx] = b; w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
int find(int u) {
    if (p[u] != u) p[u] = find(p[u]);
    return p[u];
}
LL kruskal() {
    LL res = 0;
    for (int i = 1; i <= n; ++i) p[i] = i;
    sort(edge, edge + m);
    for (int i = 0; i < m; ++i) {
        int a = find(edge[i].a), b = find(edge[i].b), c = edge[i].c;
        if (a != b) {
            res += c;
            p[a] = b;
            edge[i].tr = true;
        }
    }
    return res;
}
void build() {
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; ++i) {
        if (edge[i].tr) {
            int a = edge[i].a, b = edge[i].b, c = edge[i].c;
            add(a, b, c), add(b, a, c);
        }
    }
}
void bfs() {
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[1] = 1;
    int tt = 0, hh = 0;
    q[0] = 1;
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (depth[j] > depth[t] + 1) {
                depth[j] = depth[t] + 1;
                q[++tt] = j;
                fa[j][0] = t;
                d1[j][0] = w[i], d2[j][0] = -INF;
                for (int k = 1; k <= 16; ++k) { //从小到大更新
                    int anc = fa[j][k - 1];
                    fa[j][k] = fa[anc][k - 1];
                    int distance[4] = {d1[j][k - 1], d2[j][k - 1], d1[anc][k - 1], d2[anc][k - 1]};
                    for (int u = 0; u < 4; ++u) {
                        if (distance[u] > d1[j][k])
                            d2[j][k] = d1[j][k], d1[j][k] = distance[u];
                        else if (distance[u] != d1[j][k] && distance[u] > d2[j][k])
                            d2[j][k] = distance[u];
                    }
                }
            }
        }
    }
}
int lca(int a, int b, int c) {
    static int dist[N * 2];
    int cnt = 0;
    if (depth[a] < depth[b]) swap(a, b);
    for (int i = 16; i >= 0; --i) {
        if (depth[fa[a][i]] >= depth[b]) {
            dist[cnt++] = d1[a][i];
            dist[cnt++] = d2[a][i];
            a = fa[a][i];
        }
    }
    if (a != b) {
        for (int i = 16; i >= 0; --i) {
            if (fa[a][i] != fa[b][i]) {
                dist[cnt++] = d1[a][i];
                dist[cnt++] = d2[a][i];
                dist[cnt++] = d1[b][i];
                dist[cnt++] = d2[b][i];
                a = fa[a][i];
                b = fa[b][i];
            }
        }
        dist[cnt++] = d1[a][0]; //只走一步，是没有必要加上负无穷的次大值的
        dist[cnt++] = d1[b][0];
    }
    int dist1 = -INF, dist2 = -INF;
    for (int i = 0; i < cnt; ++i) {
        if (dist[i] > dist1) dist2 = dist2, dist1 = dist[i];
        else if (dist[i] != dist1 && dist[i] > dist2) dist2 = dist[i];
    }
    if (dist1 < c) return c - dist1;
    if (dist2 < c) return c - dist2;
    return INF;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) cin >> edge[i].a >> edge[i].b >> edge[i].c;
    LL sum = kruskal();
    build();    //建出最小生成树
    bfs(); //初始化fa和depth
    //枚举添加的非树边
    LL res = 1e18;
    for (int i = 0; i < m; ++i) {
        if (!edge[i].tr) {
            int a = edge[i].a, b = edge[i].b, c = edge[i].c;
            res = min(res, sum + lca(a, b, c));
        }
    }
    cout << res << endl;
    return 0;
}
```
