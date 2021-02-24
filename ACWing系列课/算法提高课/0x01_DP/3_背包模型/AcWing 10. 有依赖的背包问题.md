```c++
#include <iostream>
#include <cstring>
using namespace std;

/*
    问题：
        考虑第u个物品的时候，他的k个子物品的组合共有2^k种可能
        一个方案一个方案枚举是指数级别的，必定超时
    这里y总采用的方法是按照体积来枚举:
        考虑第u个物品的时候，把他的子物品用体积从0~m划分成m-1个集合
        预留出v[u]的体积给当前物品u
        然后把子物品的选择看作多重背包问题，计算每个体积的集合的最大值
    更新完所有子物品后更新当前物品u的集合:
        大于v[u]的更新值
        小于v[u]的设置为0
*/

const int N = 110;
int n, m;
int h[N], e[N], ne[N], idx;
int v[N], w[N];
int f[N][N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u) {
    //先处理子物品
    for (int i = h[u]; ~i; i = ne[i]) {
        int t = e[i];
        dfs(t);
        //对子物品进行分组背包处理
        //循环体积
        for (int j = m - v[u]; j >= 0; --j) {
            //循环方案
            for (int k = 0; k <= j; ++k) {
                //这里不同以往，以前一般是加w[k]，那是在枚举分组背包里的具体物品
                //这里加f[t][k]，是在枚举分组背包内的体积，而体积的最大值就是由集合方案存储的
                f[u][j] = max(f[u][j], f[u][j - k] + f[t][k]);
            }
        }
    }
    for (int i = m; i >= v[u]; --i) f[u][i] = f[u][i - v[u]] + w[u];
    for (int i = 0; i < v[u]; ++i) f[u][i] = 0;
}

int main() {
    memset(h, -1, sizeof h);
    int root;
    
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int p;
        cin >> v[i] >> w[i] >> p;
        if (p == -1) root = i;
        else add (p, i);
    }
    dfs(root);
    cout << f[root][m] << endl;
    return 0;
}
```

