> tarjan + dp
```c++
#include <iostream>
#include <cstring>
#include <unordered_set>

using namespace std;

typedef long long LL;
const int N = 1e5 + 10, M = 2e6 + 10;
int n, m, mod;
int h[N], hscc[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp, stk[N], top;
bool in_stk[N];
int scc_cnt, id[N], scc_size[N];
int f[N], cnt[N];   //用于dp

void add(int h[], int a, int b) {
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
        }else if (in_stk[j]) low[u] = min(low[u], dfn[j]);
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
    cin >> n >> m >> mod;
    
    memset(h, -1, sizeof h);
    memset(hscc, -1, sizeof hscc);
    while (m--) {
        int a, b;
        cin >> a >> b;
        add(h, a, b);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    //缩点建图，注意！这里的边数是有讲究的，最终统计的是最长链
    //因此，强联通分量之间的边不能有重边（即同样的两个强连通分量之间只记录一条）
    unordered_set<LL> set;  //因为set不能使用pair类型，我们这里采用一个longlong来存储
    //hash_value = u * 1e6 + b  (这样hash可行的原因是u和v的范围是1e5，不会发生碰撞)
    for (int i = 1; i <= n; ++i) {
        for (int j = h[i]; ~j; j = ne[j]) {
            int k = e[j];
            int a = id[i], b = id[k];
            LL hash = a * 1000000ll + b;
            //判断这俩强连通分量有没有这条边，有过的话就不加了
            if (a != b && !set.count(hash)) {
                add(hscc, a, b);
                set.insert(hash);   //标记该边
            }
        }
    }
    //dp
    //注意tarjan统计出来的前连通分量是逆拓扑序的
    //因此dp的初试点就在id的最后一个，因此我们逆着id做就是拓扑序了
    for (int i = scc_cnt; i; --i) {
        //初始化所有强连通分量
        if (!f[i]) {
            f[i] = scc_size[i];
            cnt[i] = 1;
        }
        for (int j = hscc[i]; ~j; j = ne[j]) {
            int k = e[j];
            if (f[k] < f[i] + scc_size[k]) {
                f[k] = f[i] + scc_size[k];
                cnt[k] = cnt[i];
            } else if (f[k] == f[i] + scc_size[k]) cnt[k] = (cnt[k] + cnt[i]) % mod;
        }
    }
    //统计最长链以及对应条数
    int maxv = 0, cntv = 0;
    for (int i = 1; i <= scc_cnt; ++i) {
        if (maxv < f[i]) maxv = f[i], cntv = cnt[i];
        else if (maxv == f[i]) cntv = (cntv + cnt[i]) % mod;
    }
    cout << maxv << endl << cntv << endl;
    return 0;
}
```