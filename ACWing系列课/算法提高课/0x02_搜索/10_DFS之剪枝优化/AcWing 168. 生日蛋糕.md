```c++
#include <iostream>
#include <cmath>
using namespace std;

const int N = 25, INF = 1e9;
int n, m;
int minv[N], mins[N];
int R[N], H[N];
int ans = INF;

//当前即将处理第u层，之前层体积是v，之前层表面积是s
void dfs(int u, int v, int s) {
    //如果已经使用的体积 + 当前层往上的最小体积 已经超过了预定体积
    //则直接剪枝
    if (v + minv[u] > n) return;
    //最优性剪枝
    if (s + mins[u] >= ans) return;
    if (s + 2 * (n - v) / R[u + 1] >= ans) return;
    
    if (!u) {
        if (v == n) ans = s;	//体积需要全部用完一个不剩
        return;
    }
    //枚举当前层的半径r和高度h
    for (int r = min(R[u + 1] - 1, (int)sqrt(n - v)); r >= u; --r) {
        for (int h = min(H[u + 1] - 1, (n - v) / r / r); h >= u; --h) {
            int t = 0;
            if (u == m) t = r * r;	//如果当前是最底层，额外加上顶部面积
            R[u] = r, H[u] = h;
            dfs(u - 1, v + r * r * h, s + t + 2 * r * h);
        }
    }
}

int main() {
    cin >> n >> m;
    //预处理i层蛋糕的最小体积和最小表面积
    //（例如：第i层至少半径为i，这样i-1层至少i-1，...，这样第1层才有1的半径可以用了）
    for (int i = 1; i <= m; ++i) {
        minv[i] = minv[i - 1] + i * i * i;
        mins[i] = mins[i - 1] + 2 * i * i;
    }
    //第m+1层（不存在的层）设立两个哨兵
    R[m + 1] = H[m + 1] = INF;
    
    dfs(m, 0, 0);   //从蛋糕底层往上dfs
    
    if (ans == INF) ans = 0;
    cout << ans << endl;
    
    return 0;
}
```

![image-20210217174204183](/Users/zhaoxiucong/Library/Application Support/typora-user-images/image-20210217174204183.png)