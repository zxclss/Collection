```c++
f[i][j]集合：
    从i-1列衍生到第i列的横方块状态是j的，前i列的方案数
f[i][j]属性：
    总数
状态计算-集合划分：
    |f(i-1, k1)
    |f(i-1, k2)
    |......
    (k1, k2, ...)是能和j结合，形成合法状态的状态
状态转移方程：
    f(i, j) = f(i - 1, k1) + f(i - 1, k2) + ... + f(i - 1, kn)
```
```c++
#include <iostream>
#include <cstring>
using namespace std;

const int N = 12, M = 1 << N;

long long f[N][M];
bool st[M];

int main() {
    int n, m;
    while (cin >> n >> m, n || m) {
        for (int i = 0; i < 1 << n; ++i) {
            int cnt = 0;
            st[i] = true;
            for (int j = 0; j < n; ++j) {
                if (i >> j & 1) {
                    if (cnt & 1) st[i] = false;
                    cnt = 0;
                } else {
                    ++cnt;
                }
            }
            if (cnt & 1) st[i] = false;
        }
        memset(f, 0, sizeof f);
        f[0][0] = 1;
        for (int i = 1; i <= m; ++i) {
            for (int j = 0; j < 1 << n; ++j) {
                for (int k = 0; k < 1 << n; ++k) {
                    if ((j & k) == 0 && st[j | k]) {
                        f[i][j] += f[i - 1][k];
                    }
                }
            }
        }
        cout << f[m][0] << endl;
    }
    return 0;
}
```


### 用vector记录与当前状态可以结合成合法状态的状态

```c++
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

typedef long long LL;
const int N = 12, M = 1 << 12;

int n, m;
LL f[N][M];
vector<int> state[M];
bool st[M];

int main() {
    while (cin >> n >> m, n || m) {
        //先构造st[]合法数组，记录可以存在的状态
        for (int i = 0; i < 1 << n; ++i) {
            int cnt = 0; //记录连续0的个数
            bool is_valid = true; //记录结果
            for (int j = 0; j < n; ++j) {
                if (i >> j & 1) {
                    //当遇到 1 时， 如果连续的 0 为奇数个，则说明不能用竖的方块填满，为不合法状态
                    if (cnt & 1) {
                        is_valid = false;
                        break;
                    }
                    cnt = 0;  //当连续的 0 为偶数个，合法的空缺
                }
                else ++cnt; //遇到 0，累加1
            }
            if (cnt & 1) is_valid = false; //枚举到最后一行时，判断最后几个 0 是否合法
            st[i] = is_valid;
        }
        //用vector记录与当前状态可以结合成合法状态的状态
        for (int i = 0; i < 1 << n; ++i) {
            state[i].clear();
            for (int j = 0; j < 1 << n; ++j) {
                if ((i & j) == 0 && st[i | j]) {
                    state[i].push_back(j);
                }
            }
        }
        //Dp
        memset(f, 0, sizeof f);
        f[0][0] = 1;
        for (int i = 1; i <= m; ++i) {
            for (int j = 0; j < 1 << n; ++j) {
                for (auto k: state[j]) {
                    f[i][j] += f[i - 1][k];
                }
            }
        }
        cout << f[m][0] << endl;
    }
    return 0;
}
```