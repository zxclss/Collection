```c++
#include <iostream>
#include <cstring>
using namespace std;

/*
自动机状态：
点:
    状态0: 匹配到子串的第0个位置
    状态1: 匹配到子串的第1个位置
    ......
    状态m: 匹配到子串的第m个位置

    入口: 匹配到字符串的第0个位置
边:
    当前字符匹配：  状态i -> 状态i+1
    当前字符不匹配：状态i -> prefix(i) -> ... -> j 根据KMP的规则一直转换直到“匹配”或“第0个字符位置”

f(i,j)状态表示:
    集合：考虑前i个枚举的位置，其第i个字母的自动机状态是j的方案
    属性：总数sum
状态转移方程：
    主要是模拟KMP算法，具体下面参照代码
*/

const int N = 52, mod = 1e9 + 7;
int n;
char str[N];
int f[N][N], prefix[N];

int main() {
    cin >> n >> str + 1;
    int m = strlen(str + 1);
    for (int i = 2, j = 0; i <= m; ++i) {
        while (j && str[i] != str[j + 1]) j = prefix[j];
        if (str[j + 1] == str[i]) ++j;
        prefix[i] = j;
    }

    f[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        //不枚举是m的情况，因为如果当前状态是m，表示出现了匹配模式串的子串，放弃这种选择
        for (int j = 0; j < m; ++j) {
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                int u = j;
                while (u && ch != str[u + 1]) u = prefix[u];
                if (ch == str[u + 1]) ++u;
                if (u < m) f[i + 1][u] = (f[i + 1][u] + f[i][j]) % mod;
            }
        }
    }
    //最后把由n个字母组成，且状态不为m的方案数都加起来，就是最终答案了
    int res = 0;
    for (int i = 0; i < m; ++i) res = (res + f[n][i]) % mod;
    cout << res << endl;
    return 0;
}
```

