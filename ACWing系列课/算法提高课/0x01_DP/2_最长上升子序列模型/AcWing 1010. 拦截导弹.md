```c++
#include <iostream>
using namespace std;

/*
    第一问是求最长下降子序列的dp问题，不做过多解释，主要讲一下第二问的贪心
    贪心流程：
        从前往后遍历每个数，对于每个数:
            情况1: 如果现有的子序列的结尾都小于当前数(目前所有炮台高度都低，拦不了)，则创建新子序列；
            情况2: 将当前数放到结尾大于它的最小子序列后面(用能打掉它的最低高度的炮台)
    如何证明贪心的答案数A与最优解数B相等？ A>=B && B>=A
        首先A是合法序列，所以A >= B是肯定的
        然后考虑最优解和贪心解在过程中的区别:
            (a < b)
            xxxxxan------   xxxxxam------
            xxxxxbm------   xxxxxbn------
            在其中的某个步骤里，最优解把m------序列接到了b后，而贪心解接到了a后
            已知a < b且m,n > a, b;
            则可以对最优解通过一次调整，交换这两个序列使其为一个方案，且方案数不增加
            那么就可以证明，贪心解数==最优解数了
            233333333333
*/

const int N = 3e4 + 10;
int n;
int q[N];
int f[N], g[N];

int main() {
    while (cin >> q[n]) ++n;
    int res = 0;
    for (int i = 0; i < n; ++i) {
        f[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (q[j] >= q[i]) {
                f[i] = max(f[i], f[j] + 1);
            }
        }
        res = max(res, f[i]);
    }
    cout << res << endl;

    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        int l = 0, r = cnt;
        //二分出贪心解的位置
        while (l < r) {
            int mid = l + r >> 1;
            if (g[mid] >= q[i]) r = mid;
            else l = mid + 1;
        }
        if (g[l] >= q[i]) g[l] = q[i];  //condition 1
        else g[cnt++] = q[i];           //condition 2
    }
    cout << cnt << endl;
    return 0;
}
```

