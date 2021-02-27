```c++
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 1e4 + 10, M = 2 * N;
int n, m;
int h[N], e[M], w[M], ne[M], idx;
int dist[N];
int st[N];
int p[N];
vector<PII> query[N];   //first存点i查询的另外一个点，second存查询的编号
int res[M];

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
void dfs(int u, int fa) {
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        dist[j] = dist[u] + w[i];
        dfs(j, u);
    }
}
int find(int u) {
    if (p[u] != u) p[u] = find(p[u]);
    return p[u];
}
void tarjan(int u) {
    st[u] = 1;  //当前在搜索的点，标记为1
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        //继续往下搜索未搜过的点
        if (!st[j]) {
            tarjan(j);
            p[j] = u;   //回溯的时候，这棵子树就合并到根节点的并查集中
        }
    }
    for (auto it: query[u]) {
        int b = it.first, i = it.second;
        if (st[b] == 2)
            res[i] = dist[b] + dist[u] - dist[find(b)] * 2;
    }
    st[u] = 2;  //往上回溯前，标记为2，表示已经搜索过且回溯
}
int main() {
    cin >> n >> m;
    
    for (int i = 1; i <= n; ++i) p[i] = i;
    
    memset(h, -1, sizeof h);
    for (int i = 1; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        //如果a==b，在res中就已经被初始化为0了，无需计算
        if (a != b) {
            query[a].push_back({b, i});
            query[b].push_back({a, i});
        }
    }
    dfs(1, -1); //先用dfs初始化所有点到根节点的距离
    tarjan(1);  //tarjan离线算法
    for (int i = 0; i < m; ++i) cout << res[i] << endl;
    return 0;
}
```