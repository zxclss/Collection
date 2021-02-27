```c++
#include <iostream>
using namespace std;

//观察到一个状态机模型：
//点：
//  状态1: 偷当前当铺
//  状态2: 不偷当前当铺
//边：
//  状态1 -> 状态1: 上一个店铺不偷，当前店铺也不偷
//  状态1 -> 状态2: 上一个店铺不偷，当前店铺偷
//  状态2 -> 状态1: 上一个店铺偷，当前店铺不偷
//
//设置状态机的入口f[0][0] = 0 和 f[0][1] = -INF

const int N = 1e5 + 10, INF = 1e9;
int T, n;
int w[N];
int f[N][2];

int main() {
    //设置状态机的入口
    f[0][0] = 0, f[0][1] = -INF;

    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);
        for (int i = 1; i <= n; ++i) {
            f[i][0] = max(f[i - 1][1], f[i - 1][0]);
            f[i][1] = f[i - 1][0] + w[i];
        }
        cout << max(f[n][0], f[n][1]) << endl;
    }
    return 0;
}
```

