```C++
#include <iostream>
using namespace std;

//从左上角进入方格，接着走到右下角的最快经过方格数为 1 + 2 * (n - 1) = 2n - 1
//所以这一题隐含意思就是，只能向右或向下走，到f[n][m]的最短时间
//就是求最小值的摘花生

const int N = 110, INF = 1e9;
int n;
int w[N][N];
int f[N][N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &w[i][j]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            //特判一开始进入方格(0, 0)的时间
            if (i == 1 && j == 1) f[i][j] = w[i][j];
            else {
                f[i][j] = INF;
                //特判上边界和左边界，便于取最小值(f[0][j]和f[i][0]默认是0，取最小值需要特判他们)
                if (i > 1) f[i][j] = min(f[i][j], f[i - 1][j] + w[i][j]);
                if (j > 1) f[i][j] = min(f[i][j], f[i][j - 1] + w[i][j]);
            }
        }
    }
    printf("%d\n", f[n][n]);
    return 0;
}
```

