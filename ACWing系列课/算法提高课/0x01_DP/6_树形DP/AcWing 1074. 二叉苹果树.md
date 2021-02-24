```c++
#include <iostream>
#include <cstring>
using namespace std;

/*
有依赖的分组背包问题简化版
物品组就是子树上选择保留的边数
f(i,j)状态表示：
    集合：考虑根结点为 i 个子树，保留 j 条边的方案
    属性：苹果数量最大值Max
f(i,j)状态计算：
    集合划分：
    k枚举保留的边数量：
        考虑左子树的物品组：（左子树只能选择一个k）
            f(i, j - 1 - k) + f(lchild(i), k) + w1
        考虑右子树的物品组：（右子树只能选择一个k）
            f(i, j - 1 - k) + f(rchild(i), k) + w1
        但是左右并不互斥，最后保留的是两者选择的k1和k2的方案的最大值
*/

const int N = 110, M = 2 * N;
int n, m;
int h[N], e[M], ne[M], w[M], idx;
int f[N][N];

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}
void dfs(int u, int father) {
    for (int i = h[u]; ~i; i = ne[i]) {
        if (e[i] == father) continue;
        dfs(e[i], u);

        //循环体积
        for (int j = m; j >= 0; --j) {
            //枚举决策
            //选择在子树上保留的边数（要留一条给子树连到根结点的边）
            for (int k = 0; k <= j - 1; ++k) {
                f[u][j] = max(f[u][j], f[u][j - k - 1] + f[e[i]][k] + w[i]);
            }
        }
    }
}
int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    dfs(1, -1);
    cout << f[1][m] << endl;
    return 0;
}
```

