> 树上差分 + LCA
```c++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 100010, M = 2 * N;
int n, m;
int h[N], e[M], ne[M], idx;
int depth[N], fa[N][17], q[N];
int d[N];
int ans;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void bfs(){
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[1] = 1;
    int hh = 0, tt = 0;
    q[0] = 1;
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (depth[j] > depth[t] + 1) {
                depth[j] = depth[t] + 1;
                q[++tt] = j;
                fa[j][0] = t;
                for (int k = 1; k <= 16; ++k)
                    fa[j][k] = fa[fa[j][k - 1]][k - 1];
            }
        }
    }
}
int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    for (int i = 16; i >= 0; --i) {
        if (depth[fa[a][i]] >= depth[b]) {
            a = fa[a][i];
        }
    }
    if (a == b) return a;
    for (int i = 16; i >= 0; --i) {
        if (fa[a][i] != fa[b][i]) {
            a = fa[a][i];
            b = fa[b][i];
        }
    }
    return fa[a][0];
}
int dfs(int u, int father) {
    int sum = d[u];
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == father) continue;
        
        int t = dfs(j, u);
        if (t == 0) ans += m;
        else if (t == 1) ++ans;
        sum += t;
    }
    return sum;
}
int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    bfs();  //初始化fa[][]和depth[]
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        int p = lca(a, b);
        ++d[a], ++d[b], d[p] -= 2; 
    }
    dfs(1, -1);
    cout << ans << endl;
    return 0;
}
```