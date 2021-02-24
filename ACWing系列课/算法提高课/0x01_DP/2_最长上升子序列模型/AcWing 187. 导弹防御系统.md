```c++
#include <iostream>
using namespace std;

// 这题是拦截拦截第二问的加强版
// 拦截导弹第二问是只考虑下降序列的方案数，因此直接用贪心搜出最优解即可(证明在那一题的笔记里)
// 这一题，确实要考虑下降和上升两种序列的方案数
// 因此只能用dfs进行爆搜两种方案的搭配，但无论是上升还是下降方案，依然采用上一题的贪心思路

const int N = 55;
int n;
int a[N];
int up[N], down[N];
int res;

//三个参数分别是考虑前u个导弹
//已经采用了上升系统个数sum_up
//和下降系统个数sum_down
void dfs(int u, int sum_up, int sum_down) {
    //如果已经超过了最优解答案，那么直接剪枝
    if (sum_up + sum_down >= res) return;
    //没有超过最优解答案，且把所有导弹都考虑到了
    //那他就是当前最优解了
    if (u == n) {
        res = sum_up + sum_down;
        return;
    }
    //情况一：考虑用上升拦截系统来拦截第u个导弹
    // 上升拦截系统的贪心思路是：
    //     如果当前已有的上升拦截系统的高度都大于第u个导弹高度，则重新开一套系统
    //     否则，则由当前低于第u个导弹最高拦截系统来负责拦截
    int k = 0;
    while (k < sum_up && up[k] >= a[u]) ++k;
    //找到了有这么个拦截系统
    int t = up[k]; //t用于dfs回溯的时候恢复现场
    up[k] = a[u];
    if (k >= sum_up) dfs(u + 1, sum_up + 1, sum_down);
    else dfs(u + 1, sum_up, sum_down);
    //恢复现场
    up[k] = t;
	
    //情况二：考虑用下降拦截系统来拦截第u个导弹
    // 下降拦截系统的贪心思路是：
    //     如果当前已有的下降拦截系统的高度都小于第u个导弹高度，则重新开一套系统
    //     否则，则由当前大于第u个导弹最低拦截系统来负责拦截
    k = 0;
    while (k < sum_down && down[k] <= a[u]) ++k;
    t = down[k]; //t用于dfs回溯的时候恢复现场
    down[k] = a[u];
    if (k >= sum_down) dfs(u + 1, sum_up, sum_down + 1);
    else dfs(u + 1, sum_up, sum_down);
    //恢复现场
    down[k] = t;
}

int main() {
    while (cin >> n, n) {
        for (int i = 1; i <= n; ++i) cin >> a[i];
        //最差情况是n个导弹分别用n个系统拦截
        //因此可以设置res初始为n来设立哨兵
        res = n;
        dfs(1, 0, 0);
        cout << res << endl;
    }
    return 0;
}
```

