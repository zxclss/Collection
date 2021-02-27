```c++
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

//这题是一道线性代数问题
//求解一个向量组的秩(最大无关向量组的维数)
//但是代码写起来就是一个模拟筛选的过程
//从小到大，先查看当前数有没有被晒掉，
//1)如果没有就把它加入到最大无关向量组中，并把他以及他和此前的硬币的线性组合都筛掉
//2)如果有就不理会
//即就是在完全背包求方案数的过程中，统计那些初始没有方案数的物品
//这样就变成一个完全背包问题了

const int N = 110, M = 25010;

int T, n;
int a[N];
int f[M];

int main() {
    cin >> T;
    while (T--) {
        memset(f, 0, sizeof f);
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        sort(a + 1, a + n + 1);

        f[0] = 1;
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            //当前数没有被筛掉，加入最大无关向量组
            if (!f[a[i]]) {
                ++res;
                //筛掉这个数和此前所有数的线性组合
                for (int j = a[i]; j < M; ++j) {
                    f[j] += f[j - a[i]];
                }
            }
        }
        cout << res << endl;
    }
    return 0;
}
```

