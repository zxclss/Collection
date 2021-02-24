先上闫氏DP分析法做预处理的部分：

$f[i][j][a][b]$ 状态表示：共有 $i$ 位数位，最高位是 $j$，当前整个数字$\overline{j A} \mod 7$ 后余数是 $a$，数每位之和模 $7$ 余 $b$。

$f[i][j][a][b]$ 属性：$s_0$表示满足该条件的数的个数，$s_1$表示满足该条件的数的一次方，$s_2$表示满足该条件的数的二次方。

$f[i][j][a][b]$ 状态计算：

为了方便记录，我们先令 $v_1 = f[i][j][a][b]$，$v_2 = f[i - 1][k][(a - j \times 10^{i-1} \mod 7)][(b - j) \mod 7]$

那么我们可以得到一个状态转移的方程：
$$
\begin{align}
	v_1s_0
	+=& t \\
	 =&v_2s_0 \\ \\
	
	v_1s_1 
	+= \overline{JA_1} + \overline{JA_2} + ···+\overline{JA_t} 
	 =& (J \times 10^{i-1}) \times t + (A_1 + A_2 + ··· + A_t) \\
	 =& (J \times 10^{i-1}) \times v_2s_0 + v_2s_1 \\ \\
	
	v_1s_2 
	+= \overline{JA_1}^2 + \overline{JA_2}^2 + ···+\overline{JA_t}^2 
	 =& (J\times10^{i-1} + A_1)^2 + (J\times10^{i-1} + A_2)^2 + ···+(J\times10^{i-1} + A_t)^2 \\
	 =& (J \times 10^{i-1})^2 \times t + 2\times J \times 10^{i-1} \times (A_1 + A_2 + ··· + A_t) + A_1^2 + A_2^2 + ··· + A_t^2 \\
	 =& (J \times 10^{i - 1})^2 \times v_2s_0 + 2\times J \times 10^{i-1} \times v_2s_1 + v_2s_2 \\ \\
	

\end{align}
$$

> 这也太难了吧，抄一下y老师的代码吧

$$
res = res + (last_a \times 10^{i+1})^2 \times vs_0 + 2\times(last_a \times 10^{i+1}) \times vs_1 + vs_2
$$

```c++
#include <iostream>
#include <vector>
using namespace std;

typedef long long LL;

const int N = 20, P = 1e9 + 7;
struct F {
    int s0, s1, s2;
}f[N][10][7][7];
int power7[N], power9[N];

int mod(LL x, int y) {
    return (x % y + y) % y;
}

void init() {
    //初始化一个数位的情况
    for (int i = 0; i <= 9; ++i) {
        if (i == 7) continue;
        auto& v = f[1][i][i % 7][i % 7];
        v.s0 += 1;
        v.s1 += i;
        v.s2 += i * i;
    }
    LL power = 10;  //i是从十位(i=2)开始迭代的，因此初始第一个数位上的数值是j*power
    for (int i = 2; i < N; ++i, power *= 10) {
        for (int j = 0; j <= 9; ++j) {
            if (j == 7) continue;   //特判最高位是7的情况
            for (int a = 0; a < 7; ++a) {
                for (int b = 0; b < 7; ++b) {
                    //以上就是状态中的4层迭代
                    //接下来枚举第二个数位上的数 k
                    for (int k = 0; k <= 9; ++k) {
                        if (k == 7) continue;  //特判数字是7的情况
                        auto &v1 = f[i][j][a][b];
                        auto &v2 = f[i - 1][k][mod(a - j * (power % 7), 7)][mod(b - j, 7)];
                        v1.s0 = (v1.s0 + v2.s0) % P;
                        v1.s1 = (v1.s1 + j * (power % P) % P * v2.s0 + v2.s1) % P;
                        v1.s2 = (v1.s2 + j * j * (power % P) % P * (power % P) % P * v2.s0 +
                                 2 * j * (power % P) % P * v2.s1 % P + 
                                 v2.s2) % P;
                    }
                }
            }
        }
    }
    //预处理一个10的i倍数mod7和P的结果
    power7[0] = power9[0] = 1;
    for (int i = 1; i < N; ++i) {
        power7[i] = power7[i - 1] * 10ll % 7;
        power9[i] = power9[i - 1] * 10ll % P;
    }
}
F get(int i, int j, int a, int b) {
    int s0 = 0, s1 = 0, s2 = 0;
    for (int x = 0; x < 7; ++x)
        for (int y = 0; y < 7; ++y) {
            if (x == a || y == b) continue;
            auto v = f[i][j][x][y];
            s0 = (s0 + v.s0) % P;
            s1 = (s1 + v.s1) % P;
            s2 = (s2 + v.s2) % P;
        }
    return {s0, s1, s2};
}
int dp(LL n) {
    if (!n) return 0;
    LL backup_n = n % P;
    vector<int> num;
    while (n) num.push_back(n % 10), n /= 10;
    
    int res = 0;
    //分别存储“前面所有数位连在一起的数”（为了复原该数位之前所用的数构成的大小，以便于减去）
    //以及“前面所有数位上的数之和”
    LL last_a = 0, last_b = 0;
    
    for (int i = num.size() - 1; i >= 0; --i) {
        int x = num[i];
        for (int j = 0; j < x; ++j) {
            if (j == 7) continue;
            int a = mod(-last_a * power7[i + 1], 7); //对应的是整个数是7的整数倍
            int b = mod(-last_b, 7); //对应的是每一位加起来是7的整数倍
            //v表示，在剩下的数位里，第i + 1位填 j，并且整个数mod7不为a，且所有数位之和mod7不为b
            auto v = get(i + 1, j, a, b);
            
            res = (res + ((last_a % P) * (last_a % P) % P * (power9[i+1] % P) % P * (power9[i+1] % P) % P * v.s0) % P + 
                    2 * (last_a % P) * (power9[i + 1] % P) % P * v.s1 + v.s2) % P;
        }
        
        if (x == 7) break;
        last_a = last_a * 10 + x;
        last_b = last_b + x;
        
        if (!i && last_a % 7 && last_b % 7) res = (res + backup_n * backup_n) % P;
    }
    return res;
}

int main() {
    init();
    int T;
    cin >> T;
    while (T--) {
        LL l, r;
        cin >> l >> r;
        cout << mod(dp(r) - dp(l - 1), P) << endl;
    }
    return 0;
}
```

