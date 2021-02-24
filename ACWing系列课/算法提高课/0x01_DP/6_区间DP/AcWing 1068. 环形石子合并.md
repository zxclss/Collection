# 环形石子合并问题——区间DP
> 拆环变链
```c++
#include <iostream>
#include <cstring>
using namespace std;

//这题我们选择把环拉成链
//做法是开两倍的数组空间
//然后区间dp的时候，迭代区间长度到n即可
//实际意义就是求数组中长度是n的区间的最值问题
//就变换成之前的石子合并啦

const int N = 410, INF = 0x3f3f3f3f;
int n;
int w[N], sum[N];
int f[N][N], g[N][N];
//f求最大值，g求最小值

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
        w[i + n] = w[i]; //拷贝前半数组到后半部分
    }
    //求前缀和
    for (int i = 1; i <= 2 * n; ++i) sum[i] = w[i] + sum[i - 1];
    
    memset(f, -0x3f, sizeof f); //求最大值初始化为无穷小
    memset(g,  0x3f, sizeof g); //求最小值初始化为无穷大
    
    //一颗石子不需要合并，这一步也可以写在循环中特判len==1的情况
    //为了方便理解，我额外写了一个循环
    for (int i = 1; i <= 2 * n; ++i) f[i][i] = g[i][i] = 0;
    
    for (int len = 2; len <= n; ++len) {
        for (int left = 1; left + len - 1 <= 2 * n; ++left) {
            int right = left + len - 1;
            //枚举分割石子的中点k
            for (int k = left; k < right; ++k) {
                f[left][right] = max(f[left][right], f[left][k] + f[k + 1][right] + sum[right] - sum[left - 1]);
                g[left][right] = min(g[left][right], g[left][k] + g[k + 1][right] + sum[right] - sum[left - 1]);
            }
        }
    }
    int maxV = -INF, minV = INF;
    for (int left = 1; left <= n; ++left) {
        maxV = max(maxV, f[left][left + n - 1]);
        minV = min(minV, g[left][left + n - 1]);
    }
    cout << minV << endl << maxV << endl;
    
    return 0;
}

```