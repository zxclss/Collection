```c++
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

/*
线性dp预处理
f(i,j,k):数位为i的数，最高位为j，所有数位求和取模是k的方案数
集合划分:
    次高位取0, f(i-1, 0, (k-j) mod P)
    次高位取1, f(i-1, 1, (k-j) mod P)
    ...
    次高位取9, f(i-1, 9, (k-j) mod P)
状态转移方程，对上述求和即可
*/

const int N = 15, M = 110;
int P;
int f[N][10][M];

int mod(int n, int k) {
    return (n % k + k) % k;
}
void init() {
    memset(f, 0, sizeof f);
    //初始化
    for (int i = 0; i <= 9; ++i) ++f[1][i][mod(i, P)];
    
    for (int i = 2; i < N; ++i)
        for (int j = 0; j <= 9; ++j)
            for (int k = 0; k < P; ++k)
                for (int x = 0; x <= 9; ++x)
                    f[i][j][k] += f[i - 1][x][mod(k - j, P)];
}
int dp(int n) {
    if (!n) return 1;
    vector<int> num;
    while (n) num.push_back(n % 10), n /= 10;
    
    int res = 0;
    int last = 0;  //统计前几位位数的和
    
    for (int i = num.size() - 1; i >= 0; --i) {
        int x = num[i];
        for (int j = 0; j < x; ++j)
            res += f[i + 1][j][mod(-last ,P)];
        
        last += x;
        if (!i && mod(last, P) == 0) ++res;
    }
    return res;
}
int main() {
    int l, r;
    while (cin >> l >> r >> P) {
        init();
        cout << dp(r) - dp(l - 1) << endl;
    }
    return 0;
}
```

