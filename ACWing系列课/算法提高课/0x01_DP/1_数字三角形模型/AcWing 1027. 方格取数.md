```c++
#include <iostream>
using namespace std;

/*
    状态表示: f[i1][j1][i2][j2] 
    	集合: 从起点第一轮走到(i1,j1)，第二轮走到(i2,j2)，的方案
        属性: 最大值
    优化: 第一轮和第二轮出现取相同格子内的数的情况出现在 i1==i2 && j1==j2   =>  i1+i2==j1+j2
          因此可以用k来记录i1 + i2和j1 + j2的值，把四维优化到三维
          f[k][i1][i2]: j1=k-i1, j2=k-i2

    状态计算: 考虑当前集合能从哪些集合转移过来，分别是：
        (1) 第一轮的左边一格、第二轮的左边一格 f[k - 1][i1 - 1][i2 - 1]
        (2) 第一轮的左边一格、第二轮的上边一格 f[k - 1][i1 - 1][i2]
        (3) 第一轮的上边一格、第二轮的左边一格 f[k - 1][i1][i2 - 1]
        (4) 第一轮的上边一格、第二轮的上边一格 f[k - 1][i1][i2]
        对第一轮和第二轮当前走到的格子进行取数 w[i1][k - i1] + w[i2][k - i2]
        *特判如果当前第一、第二轮走到了相同的格子内: i1 == i2，则只加其中一个w即可(第二轮不能取第一轮中取过的数)
        于是有状态转移方程：
        f[k][i1][i2] = w + max(f[k - 1][i1 - 1][i2 - 1], f[k - 1][i1 - 1][i2], f[k - 1][i1][i2 - 1], f[k - 1][i1][i2]);
*/

const int N = 11;

int n, a, b, c;
int w[N][N];
int f[2 * N][N][N];

int main() {
    cin >> n;
    while (cin >> a >> b >> c, a || b || c) w[a][b] = c;

    for (int k = 1; k <= n + n; ++k) {
        for (int i1 = 1; i1 <= n; ++i1) {
            for (int i2 = 1; i2 <= n; ++i2) {
                //判断越界
                if (k - i1 <= 0 || k - i1 > n || k - i2 <= 0 || k - i2 > n) continue;
                //判断是否两轮会走到相同格子
                int w_temp = w[i1][k - i1];
                if (i1 != i2) w_temp += w[i2][k - i2];
                //一顿操作1234
                f[k][i1][i2] = max(f[k][i1][i2], w_temp + f[k - 1][i1 - 1][i2 - 1]);
                f[k][i1][i2] = max(f[k][i1][i2], w_temp + f[k - 1][i1 - 1][i2]);
                f[k][i1][i2] = max(f[k][i1][i2], w_temp + f[k - 1][i1][i2 - 1]);
                f[k][i1][i2] = max(f[k][i1][i2], w_temp + f[k - 1][i1][i2]);
            }
        }
    }
    printf("%d\n", f[2 * n][n][n]);
    return 0;
}
```

