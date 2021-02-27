```c++
#include <iostream>
using namespace std;

// 状态表示f[i][j][k]
//     集合：考虑前i个物品，体积v1不多于j，体积v2不多于k的方案
//     属性：最大值
// 状态计算
//     集合划分:(就是一个二维费用的0-1背包问题)
//         1)不选第i个物品:f[i-1][j][k]
//         2)选第i个物品(前提是j和k分别大于v1[i],v2[i]):f[i-1][j-v1[i]][k-v2[i]]


const int N = 1010;
int n, V1, V2;
int f[N][N];

int main() {
    cin >> V1 >> V2 >> n;
    for (int i = 1, v1, v2; i <= n; ++i) {
        cin >> v1 >> v2;
        for (int j = V1; j >= v1; --j) {
            //体力不能归零，所以体力上限费用要留1
            for (int k = V2 - 1; k >= v2; --k) {
                f[j][k] = max(f[j][k], f[j - v1][k - v2] + 1);
            }
        }
    }
    cout << f[V1][V2 - 1] << " ";
    for (int i = 0; i <= V2 - 1; ++i) {
        if (f[V1][i] == f[V1][V2 - 1]) {
            cout << V2 - i << endl;
            break;
        }
    }
    return 0;
}
```

