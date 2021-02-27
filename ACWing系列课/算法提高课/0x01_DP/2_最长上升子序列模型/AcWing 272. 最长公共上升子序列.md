# 主要思路 + 朴素写法
```C++
#include <iostream>
using namespace std;

// 状态表示f[i][j]
//     集合:
//         考虑a中前i个数字的和b中前j个数字的公共子序列(最长公共子序列)，且以b[j]结尾上升子序列(最长上升子序列)
//     属性:
//         Max
// 状态计算:
//     集合划分:
//         1)不包含a[i]的最长公共上升子序列 f[i-1][j]
//         2)包含a[i]的最长公共上升子序列:(必须满足a[i] == b[j])
//             1.1)最长公共上升子序列的倒数第二个数是b[j-1]
//             1.2)最长公共上升子序列的倒数第二个数是b[j-2]
//             ......
//             1.k-1)最长公共上升子序列的倒数第二个数是b[1]
//             1.k)最长公共上升子序列的倒数第二个数是空
//             上述k个子集必须满足b[k] < b[j]  (必须要是上升子序列)
//             状态转移方程: f[i-1][k] + 1
//         在这些集合中取最大值即可
const int N = 3010;
int n;
int a[N], b[N];
int f[N][N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            f[i][j] = f[i - 1][j];
            if (a[i] == b[j]) {
                f[i][j] = max(f[i - 1][j], 1);
                for (int k = 1; k < j; ++k) {
                    if (b[k] < b[j]) {
                        f[i][j] = max(f[i][j], f[i - 1][k] + 1);
                    }
                }
            }
        }
    }
    
    int res = 0;
    for (int i = 1; i <= n; ++i) res = max(res, f[n][i]);
    printf("%d\n", res);
    
    return 0;
}
```
## 上述代码中的三重循环可以写成如下形式
用maxv来存储最大值
```C++
for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
        f[i][j] = f[i - 1][j];
        if (a[i] == b[j]) {
            int maxv = 1;
            for (int k = 1; k < j; ++k) {
                if (b[k] < a[i])
                    maxv = max(maxv, f[i-1][k] + 1);
                //可以观察到maxv的比较用到了[i][k]层的状态
                //(而k < j)说明这是上一层的状态
                //而maxv存储的正是上一层状态中的最大值
                //因此既然用了旧状态中的最大值，那么就可以优化掉这个找上层最大值的循环了
                //即用一个变量maxv来存储上一层的最大值
                f[i][j] = max(maxv, f[i][j]);
            }
        }
    }
}

//改写成这个样子
for (int i = 1; i <= n; ++i) {
    int maxv = 1; //maxv的含义就是f[i][j-1]～f[i][1]中满足a[i]>b[k]的最大值
    for (int j = 1; j <= n; ++j) {
        f[i][j] = f[i - 1][j];
        //这个a[i]>b[j]对应的是上面代码中的a[i]>b[k]的判断
        if (a[i] > b[j]) maxv = max(maxv, f[i-1][j] + 1);
        if (a[i] == b[j]) f[i][j] = max(f[i][j], maxv);
    }
}
```



# 代码优化后的完整代码

(跟思路无关，单纯对于等价代码进行优化)

```C++
#include <iostream>
using namespace std;
const int N = 3010;
int n;
int a[N], b[N];
int f[N][N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);
    
    for (int i = 1; i <= n; ++i) {
        int maxv = 1;
        for (int j = 1; j <= n; ++j) {
            f[i][j] = f[i - 1][j];
            if (a[i] > b[j]) maxv = max(maxv, f[i-1][j] + 1);
            if (a[i] == b[j]) f[i][j] = max(f[i][j], maxv);
        }
    }
    
    int res = 0;
    for (int i = 1; i <= n; ++i) res = max(res, f[n][i]);
    printf("%d\n", res);
    
    return 0;
}

```