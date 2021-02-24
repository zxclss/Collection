```c++
#include <iostream>
#include <cstring>
using namespace std;

/*
这题的合并就是(i, j) 与 (j, k) => (i, k)的过程
类似于啊一个ixj的矩阵和jxk的矩阵合并成ixk的过程一样
因此我们可以用一个数组存储下所有的独立值，然后模拟这个过程，比如:
i_j_k => i_k + i*j*k
观察到，合并操作区间长度至少是3，才能完成一次合并
上述就是模拟的方法，剩下的就是完全类似于环形区间DP的问题了
*/

const int N = 210;
int n;
int  w[N];
int f[N][N];

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> w[i], w[i + n] = w[i];

    //注意这里是枚举到区间长度是n+1
    //因为最后要合并为一个
    //(2, 3), (3, 4), (4, 5), (5, 2)的合并实际上是2, 3, 4, 5, 2的合并，最后还要把初始头也合并了
    for (int len = 3; len <= n + 1; ++len) {
        for (int left = 1; left + len - 1 <= 2 * n; ++left) {
            int right = left + len - 1;
            //k是不能枚举边界的，具体参考上述说的矩阵运算，只能从中间数下手，合并两边
            //变成 3 -> 2 的过程
            for (int k = left + 1; k < right; ++k) {
                f[left][right] = max(f[left][right], f[left][k] + f[k][right] + w[left] * w[right] * w[k]);
            }
        }
    }
    int res = 0;
    //最后这个枚举是要枚举到头的，第i个元素的头在n+i的位置
    for (int i = 1; i <= n; ++i)
        res = max(res, f[i][i + n]);
    cout << res << endl;
    return 0;
}
```

