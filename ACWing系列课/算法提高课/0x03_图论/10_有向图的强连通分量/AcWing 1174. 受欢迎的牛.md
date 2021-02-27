```c++
#include <iostream>
#include <cstring>

using namespace std;

//被所有牛欢迎，旨在求拓扑排序中，最后一个强连通分量中点的数量
//只能有一个出度为0的点，如果有两个，那就意味着两者互相"不喜欢"
//那么就不存在所有人都喜欢的情况了

const int N = 1e4 + 10, M = 5e4 + 10;
int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, scc_size[N];
int outdegree[N];

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
            ++scc_size[scc_cnt];
        } while (y != u);
    }
}
int main() {
    cin >> n >> m;
    
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }
    //找出所有的强连通分量
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }
    //缩点
    for (int i = 1; i <= n; ++i) {
        for (int j = h[i]; ~j; j = ne[j]) {
            int k = e[j];
            int a = id[i], b = id[k];
            if (a != b) ++outdegree[a]; //不在一个强连通分量中，就连一条a-b的边
        }
    }
    //统计，出度为0的点只能有一个
    int sum = 0, zeroCnt = 0;
    for (int i = 1; i <= scc_cnt; ++i) {
        if (outdegree[i] == 0) {
            sum += scc_size[i];
            ++zeroCnt;
            if (zeroCnt > 1) {
                sum = 0;
                break;
            }
        }
    }
    cout << sum << endl;
    return 0;
}
```