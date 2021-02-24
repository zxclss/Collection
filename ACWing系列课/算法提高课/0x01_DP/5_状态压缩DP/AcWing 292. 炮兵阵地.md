```c++
#include <iostream>
#include <vector>
using namespace std;

/*
f(i,j,k)状态表示
    摆好前i行，第i-1行状态是j，第i行状态是k的方案的集合
    最大值Max
f(i,j,k)状态计算
    集合划分
        1）从i-2层状态是0的状态转移过来的
        2）从i-2层状态是1的状态转移过来的
        3）从i-2层状态是10的状态转移过来的
        ........
        m）从i-2层状态是11..11的状态转移过来的
        以上的状态仍然需要满足合法：
            第i行、i-1行、i-2行状态两两不能相交
            i-1层和i层是不能在山地放置的
     转移方程
        f(i,j,k) = max(f(i,j,k), f(i-1, u, j) + cnt[k]) (其中j是i-1层状态,k是i层状态,u是i-2层状态)
*/
const int N = 110, M = 1 << 10;
int n, m;
int g[N];
int f[2][M][M];
vector<int> state;
int cnt[M];

bool check(int state) {
    for (int i = 0; i < m - 1; ++i)
        if ((state >> i & 1) && (state >> i + 1 & 1 || state >> i + 2 & 1))
            return false;
    return true;
}
int count(int state) {
    int res = 0;
    for (int i = 0; i < m; ++i) res += state >> i & 1;
    return res;
}
int main() {
    cin >> n >> m;
    //读入
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            g[i] += (c == 'H') << j;
        }
    }
    //预处理合法方案
    for (int i = 0; i < 1 << m; ++i)
        if (check(i)) {
            state.push_back(i);
            cnt[i] = count(i);
        }
        
    //dp
    for (int i = 1; i <= n + 2; ++i)
        for (int j = 0; j < state.size(); ++j)
            for (int k = 0; k < state.size(); ++k)
                for (int u = 0; u < state.size(); ++u) {
                    //a是i-1层状态, b是i层状态, c是i-2层状态
                    int a = state[j], b = state[k], c = state[u];
                    if ((g[i - 1] & a) | (g[i] & b)) continue;
                    //当前是合法状态的放置不能在高地"H"上
                    if ((a & b) | (a & c) | (b & c)) continue;  
                    //枚举的第i-2层状态不能和当前两层状态，两两之间不能出现交集
                    f[i & 1][j][k] = max(f[i & 1][j][k], f[i - 1 & 1][u][j] + cnt[b]);
                }
    cout << f[n + 2 & 1][0][0] << endl;
    return 0;
}
```