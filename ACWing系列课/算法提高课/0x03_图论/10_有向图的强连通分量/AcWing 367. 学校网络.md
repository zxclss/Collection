> tarjan算法求SCC强连通分量 + 添加有限边把拓扑图变成强连通图的方法
```c++
#include <iostream>
#include <cstring>

using namespace std;

//这题的第一问是求入度为0的强连通分量个数
//第二问是要通过一定证明得出的一个结论
//即如果想要把一个拓扑图通过加边，构成一个强连通图，那么边数=max(a,b);
//其中a为出度为0的强连通块个数，b为入度为0的强连通块个数
//证明非常巧妙~~~

const int N = 110, M = N * N;
int n;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int id[N], scc_cnt;
int stk[N], top;
bool in_stk[N];
int indegree[N], outdegree[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
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
    if (dfn[u] == low[u]) {
        int y;
        ++scc_cnt;
        do {
            y = stk[top--];
            in_stk[y] = false;
            id[y] = scc_cnt;
        } while (y != u);
    }
}
int main() {
    cin >> n;
    
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; ++i) {
        int t;
        while (cin >> t, t)
            add(i, t);
    }
    //tarjan
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    //缩点
    for(int i = 1; i <= n; ++i) {
        for (int j = h[i]; ~j; j = ne[j]) {
            int k = e[j];
            int a = id[i], b = id[k];
            if (a != b) {
                ++outdegree[a];
                ++indegree[b];
            }
        }
    }
    int r1, r2; //r1统计入度为0的点，r2统计出度为0的点
    for (int i = 1; i <= scc_cnt; ++i) {
        if (indegree[i] == 0) ++r1;
        if (outdegree[i] == 0) ++r2;
    }
    //第一问
    cout << r1 << endl;
    //第二问
    if (scc_cnt == 1) cout << 0 << endl;    //特判，如果一开始就是强联通的，那就不需要加边
    else cout << max(r1, r2) << endl;
    return 0;
}
```