# 高精度 + 区间DP
```c++
#include <iostream>
#include <vector>
using namespace std;

typedef long long LL;
const int N = 52;

/*
这题是“高精度” + “区间DP”两个模版的缝合版
甚至区间dp用的状态转移方程和“能量项链”那题一摸一样
就当是默写高精度吧
*/

int n;
int w[N];
vector<int> f[N][N];

//这里可能会越界，1e9 * x，所以咱们用long long
void mul(vector<int>& vec, LL a) {
    vector<int> res;
    LL t = 0;
    for (int i = 0; i < vec.size() || t; ++i) {
        if (i < vec.size()) t += vec[i] * a;
        res.push_back(t % 10);
        t /= 10;
    }
    vec = res;
}
void plu(vector<int>& a, vector<int>& b) {
    vector<int> res;
    int t = 0;
    for (int i = 0; i < a.size() || i < b.size() || t; ++i) {
        if (i < a.size()) t += a[i];
        if (i < b.size()) t += b[i];
        res.push_back(t % 10);
        t /= 10;
    }
    a = res;
}
bool gt(vector<int>& a, vector<int>& b) {
    if (a.size() != b.size()) return a.size() > b.size();
    for (int i = a.size() - 1; i >= 0; --i) {
        if (a[i] != b[i]) return a[i] > b[i];
    }
    return false;;
}
void print(vector<int>& a) {
    for (int i = a.size() - 1; i >= 0; --i)
        printf("%d", a[i]);
    puts("");
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> w[i];
    
    for (int len = 3; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;
            f[l][r] = vector<int>(32, 1);
            for (int k = l + 1; k < r; ++k) {
                vector<int> tmp({w[l]});
                mul(tmp, w[k]);
                mul(tmp, w[r]);
                plu(tmp, f[l][k]);
                plu(tmp, f[k][r]);
                // print(tmp);
                if (!gt(tmp, f[l][r])) f[l][r] = tmp;
            }
        }
    }
    print(f[1][n]);
    return 0;
}
```