```c++
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

const int N = 50;

int m, n, k;
int res;
int w[N];
int weights[1 << 25], cnt = 1;  //weights[0]是初始存在的方案(一个礼物也不搬)
//weights存储的是前k个物品的所有合法组合方案的体积值

void dfs1(int u, int s) {
    //dfs出前[0,k)的组合方案
    if (u == k) {
        weights[cnt++] = s;
        return;
    }
    dfs1(u + 1, s);  //不选第u个物品
    if ((LL)s + w[u] <= m) dfs1(u + 1, s + w[u]);   //选第u个物品
}
void dfs2(int u, int s) {
    //dfs出后[k, n]的组合方案
    if (u == n) {
        {
            //二分出表中与当前方案的s的和小于上限m的最大值
            int l = 0, r = cnt - 1;
            while (l < r) {
                int mid = l + r + 1 >> 1;
                if ((LL)weights[mid] + s <= m) l = mid;
                else r = mid - 1;
            }
            res = max(res, s + weights[r]);
            return;
        }
    }
    dfs2(u + 1, s);
    if ((LL)s + w[u] <= m) dfs2(u + 1, s + w[u]);
}
int main() {
    cin >> m >> n;
    for (int i = 0; i < n; ++i) cin >> w[i];
    
    //从大到小爆搜方案，优先搜索分支较少的方案
    sort(w, w + n);
    reverse(w, w + n);
    
    //对前k个方案打表
    k = n / 2 + 2;
    dfs1(0, 0);
    
    //排序去重
    sort(weights, weights + cnt);
    cnt = unique(weights, weights + cnt) - weights;
    
    //对后[k, n]个方案爆搜
    dfs2(k, 0);
    cout << res << endl;
    
    return 0;
}
```

