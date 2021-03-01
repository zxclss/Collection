```c++
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

typedef unsigned long long ULL;
const int N = 1010, M = 1010;
int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp, stk[N], top;
int dcc_cnt;
vector<int> dcc[N];
bool cut[N];
int root;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u;
    //孤立的单独点单独作为一个dcc，直接处理返回
    if (u == root && h[u] == -1) {
        ++dcc_cnt;
        dcc[dcc_cnt].push_back(u);
        return;
    }
    //非孤立点，把他的dcc全搜出来
    int cnt = 0;    //u连接的子树数量
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
            if (dfn[u] <= low[j]) {   //j能走到u，但是走不到u的祖先结点，u可能是割点
                ++cnt;  //j所在的环内视作u的一棵子树
                //u不是根节点，则一定是割点
                //u是根节点，但是有两棵子树的话，剪掉u，会有两个dcc
                if (u != root || cnt > 1) cut[u] = true;
                ++dcc_cnt;
                int y;
                do {
                    y = stk[top--];
                    dcc[dcc_cnt].push_back(y);
                } while (y != j);   //注意这里是j不是u
                //u是割点，而我们要回收的是u的其中一颗子树j所在的dcc
                dcc[dcc_cnt].push_back(u);//我们把割点存到每个dcc内部
            }
        } else low[u] = min(low[u], dfn[j]);
    }
}
int main() {
    int T = 1;
    while (cin >> m, m) {
        for (int i = 1; i <= dcc_cnt; i ++ ) dcc[i].clear();
        memset(h, -1, sizeof h);
        memset(dfn, 0, sizeof dfn);
        memset(cut, 0, sizeof cut);
        dcc_cnt = idx = root = timestamp = top = n = 0;
        
        while (m--) {
            int a, b;
            cin >> a >> b;
            n = max(n, a), n = max(n, b);
            add(a, b), add(b, a);
        }
        
        for (root = 1; root <= n; ++root)
            if (!dfn[root])
                tarjan(root);
        
        int res = 0;
        ULL num = 1;
        for (int i = 1; i <= dcc_cnt; ++i) {
            //搜索每个dcc，枚举删掉的点
            int cnt = 0;    //统计dcc的割点数
            for (int j = 0; j < dcc[i].size(); ++j)
                if (cut[dcc[i][j]]) ++cnt;
            if (cnt == 0) {
                //没有割点的dcc是一个单纯的连通图，那么去掉任意一个点仍是连通的
                if (dcc[i].size() > 1) res += 2, num *= dcc[i].size() * (dcc[i].size() - 1) / 2;
                else ++res;
            } else if (cnt == 1) res ++, num *= dcc[i].size() - 1;
        }
        printf("Case %d: %d %llu\n", T ++, res, num);
    }
    return 0;
}

```