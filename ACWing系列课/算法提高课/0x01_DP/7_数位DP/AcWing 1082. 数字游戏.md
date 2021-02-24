```c++
#include <iostream>
#include <vector>
using namespace std;

/*
这题需要用到两个dp：数位dp求解、线性dp预处理合法方案
数位dp用的标准模板，具体细节写在代码注释里
这里写一下线性dp的思路
f(i,j)集合：构成 i 位的不降数，最高位位 j 的数的集合
      属性：方案个数Count
f(i,j)集合划分：
            1)此高位为j  的数   f(i-1,j)
            2)此高位为j-1的数   f(i-1,j-1)
            ...
            k)此高位为9  的数   f(i-1,9)
状态计算: 对上述方案全部求和即可
*/

const int N = 15;
int a, b;
int f[N][N];

void init() {
    //所有只有一位数字的都是合法方案
    for (int i = 0; i <= 9; ++i) f[1][i] = 1;
    //dp
    for (int i = 2; i <= N; ++i)
        for (int j = 0; j <= 9; ++j)
            for (int k = j; k <= 9; ++k)
                f[i][j] += f[i - 1][k];
}
int dp(int n){
    if (!n) return 1;
    vector<int> num;
    while (n) num.push_back(n % 10), n /= 10;
    
    int res = 0;
    int last = 0;
    
    for (int i = num.size() - 1; i >= 0; --i) {
        int x = num[i];
        //枚举左子树上所有合法的方案
        for (int k = last; k < x; ++k)
            res += f[i + 1][k];
        //如果当前数位的最大值小于前一个数位，说明这条右子树是走不通的，break掉
        if (x < last) break;
        last = x;
        
        //判断右子树是否合法走到底了，走到底就要加上以这个当前这个数作为方案的方案数
        if (!i) ++res;
    }
    return res;
}
int main() {
    init();
    
    while (cin >> a >> b) cout << dp(b) - dp(a - 1) << endl;
    
    return 0;
}
```