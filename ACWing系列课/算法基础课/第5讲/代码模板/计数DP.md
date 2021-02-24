# 完全背包解法

```C++
f[i][j]表示集合：
  用到前i个数，且总和为j的方案数
  
集合的属性：
 	总数
  
状态转移方程：
  f[i][j] = f[i - 1][j] + f[i - 1][j - i] + f[i - 1][j - 2i] + ... + f[i - 1][j - si]
  f[i][j - i] =           f[i - 1][j - i] + f[i - 1][j - 2i] + ... + f[i - 1][j - si]
上述两个方程得出：
	f[i][j] = f[i - 1][j] + f[i][j - i]

维度优化
	f[j] = f[j](旧状态) + f[j - i](新状态); //小的要求旧状态，因此从前往后遍历
```

```C++
#include <iostream>
using namespace std;

const int N = 1010, mod = 1e9 + 7;
int n;
int f[N];

int main() {
    scanf("%d", &n);
    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            f[j] = (f[j] + f[j - i]) % mod;
        }
    }
    printf("%d\n", f[n]);
    return 0;
}
```



# 另一种解法

```C++
状态表示-集合f[i][j]：
  	所有总和为i，且恰好表示成j个数的方案个数
  
状态表示-属性：
  	数量
  
状态计算-集合划分：
    ｜构成的数中有1的方案：  f[i - 1][j - 1]
    ｜构成的数中没有1的方案：f[i - j][j]  (所有构成的数都减去1)
  
状态计算-状态转移方程：
    f[i][j] = f[i - 1][j - 1] + f[i - j][j]
```

```C++
#include <iostream>
using namespace std;

const int N = 1010, mod = 1e9 + 7;
int n;
int f[N][N];

int main() {
    scanf("%d", &n);
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            f[i][j] = (f[i - 1][j - 1] + f[i - j][j]) % mod;
        }
    }
    int res = 0;
    for (int i = 1; i <= n; ++i) res = (res + f[n][i]) % mod;
    printf("%d\n", res);
    return 0;
}
```

