```c++
#include <iostream>
#include <vector>
using namespace std;

//线性dp预处理，数位dp求答案

const int N = 11;
int n;
int f[N][N];

void init() {
    for (int i = 0; i <= 9; ++i) f[1][i] = 1;
    for (int i = 2; i < N; ++i)
        for (int j = 0; j <= 9; ++j)
            for (int k = 0; k <= 9; ++k)
                if (abs(j - k) >= 2)
                    f[i][j] += f[i - 1][k];
}
int dp(int n) {
    if (!n) return 0;
    vector<int> num;
    while (n) num.push_back(n % 10), n /= 10;

    int res = 0;
    int last = -2;  //满足第一位填任何数（1～9）都是合法的初始last

    for (int i = num.size() - 1; i >= 0; --i) {
        int x = num[i];
        //第一位不能是 0，即全数位统计的时候，不能出现前导零
        for (int j = i == num.size() - 1; j < x; ++j) {
            if (abs(j - last) >= 2) {
                res += f[i + 1][j];
            }
        }
        if (abs(x - last) < 2) break;
        last = x;

        if (!i) ++res;
    }

    //特殊处理，非全数位统计的时候（有前导零的情况）的方案数
    //都在预处理的矩阵里了
    for (int i = 1; i < num.size(); ++i)
        for (int j = 1; j <= 9; ++j)
            res += f[i][j];
    return res;
}
int main() {
    init();

    int a, b;
    cin >> a >> b;
    cout << dp(b) - dp(a - 1) << endl;

    return 0;
}
```

