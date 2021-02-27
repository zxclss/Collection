```c++
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int N = 35;
int K, B;
int f[N][N];

void init() {
    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (!j) f[i][j] = 1;
            else f[i][j] = f[i - 1][j - 1] + f[i - 1][j];
        }
    }
}
int dp(int x) {
    if (!x) return 0;
    vector<int> num;
    while (x) num.push_back(x % B), x /= B;

    int res = 0;  //记录答案数
    int last = 0; //统计树的右边路径下去的时候，当前已经统计了"1"多少次

    for (int i = num.size() - 1; i >= 0; --i) {
        int x = num[i];
        //只有当前位非0，我们才能枚举他小于或等于当前位的两种情况（对应左右子树）
        //否则只有可能等于当前位0（也就是对应只有右子树），只能继续往下走
        if (x) {
            //有了左子树，那么我们就能先统计到当前位非我们要统计的数（1）的情况
            res += f[i][K - last];
            //本题要统计的是1，所以要统计当前位为我们要统计的数（1）的情况，那么当前位必须大于1
            if (x > 1) {
                //当前位为1的情况：
                //这里还需特判当前剩余的1的个数是否够用
                if (K - last - 1 >= 0) res += f[i][K - last - 1];
                //这里的break是题目的要求
                //题目说所有的位要么是0，要么是1
                //因此不存在某一位是大于1的，于是我们需要对右子树进行剪枝
                break;
            }
            //else处理的就是当前位 x == 1 的情况，也就是走右子树下去
            else {
                ++last;
                //如果1不够用了，直接剪枝
                if (last > K) break;
            }
        }
        //如果根据右子树，一路走下来到最后一位了，那么判断一下当前数是不是一个合法方案
        if (!i && last == K) ++res;
    }
    return res;
}

int main() {
    //先预处理出所有的组合数
    init();
    int x, y;
    cin >> x >> y >> K >> B;
    cout << dp(y) - dp(x - 1) << endl;
    return 0;
}
```

