```c++
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 20;
int n, m;
int w[N];
int sum[N];
int res;

void dfs(int u, int group) {
    //最优解剪枝
    if (group >= res) return;
    if (u == n) {
        res = group;
        return;
    }
    //当前猫与前面的车合并
    for (int i = 0; i < group; ++i) {
        //可行性剪枝
        if (sum[i] + w[u] <= m) {
            sum[i] += w[u];
            dfs(u + 1, group);
            sum[i] -= w[u];
        }
    }
    //当前猫新开一辆车
    sum[group] = w[u];
    dfs(u + 1, group + 1);
    sum[group] = 0;
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> w[i];
    res = n;
    
    //优化搜索顺序
    sort(w, w + n);
    reverse(w, w + n);
    
    dfs(0, 0);
    cout << res << endl;
    return 0;
}
```

