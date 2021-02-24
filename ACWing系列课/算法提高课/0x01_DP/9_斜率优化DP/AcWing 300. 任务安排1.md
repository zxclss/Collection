# 没有做斜率优化
```c++
#include <iostream>
#include <cstring>
using namespace std;

/*
这题的精髓是，把第i个批次的启动费用对于后面所有批次的影响，全部累加到当前批次的结束位置
是一个区间的证明（具体参见离散数学）
f(i)状态表示：
    集合：完成前i个任务的所有方案
    属性：费用最小Min
f(i)状态计算：
    集合划分：
        不算以任务i为结束的批次的，倒数第二个批次是以i-1结尾
        不算以任务i为结束的批次的，倒数第二个批次是以i-2结尾
        ......
        不算以任务i为结束的批次的，倒数第二个批次是以0结尾
    状态转移方程：
        f(i) = min{f(j) + t_i*(c_i - c_j) + s*(c_N - c_j)}
        (0 <= j < i)
*/
const int N = 5010;
int n, s;
int t[N], c[N]; //前缀和
int f[N];

int main() {
    scanf("%d%d", &n, &s);
    for (int i = 1; i <= n; ++i) 
        scanf("%d %d", &t[i], &c[i]), t[i] += t[i - 1], c[i] += c[i - 1];
        
    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            f[i] = min(f[i], f[j] + t[i] * (c[i] - c[j]) + s * (c[n] - c[j]));
        }
    }
    printf("%d\n", f[n]);
    return 0;
}


```

