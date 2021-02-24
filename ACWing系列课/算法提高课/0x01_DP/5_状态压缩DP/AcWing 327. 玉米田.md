```c++
[//]: # (打卡模板，上面预览按钮可以展示预览效果 ^^)
​```
#include <iostream>
#include <vector>
using namespace std;

//这题和前一道"小国王"差不多，不做过多笔记，代码基本一致
//不同的是"小国王"是"井"字型的，"玉米田"是"十"字型的
//f(i,j)表示摆好了前i行土地，第i行状态是j的方案的集合

const int N = 14, M = 1 << 12, mod = 1e8;
int n, m;
int g[N];
//g[i]用于存储第i行不能种植的土地
//其逻辑意义是一个二进制串，如果第j位二进制位为1，代表第i行(j+1)列是不孕不育的土地，不能种植
//这样，加进行状态计算的时候，只需把合法状态与该合法土地状态做&运算
//如果非0，代表出现了在不育土地种植情况，这种状态就是不合法的了
//注意这里是j+1列，因为我们的状态压缩是从0列开始的，第j位二进制位的实际意义是第j+1列的状态
int f[N][M];
vector<int> state;
vector<int> head[M];

bool check(int state) {
    for (int i = 0; i < m - 1; ++i)
        if ((state >> i & 1) && (state >> i + 1 & 1))
            return false;
    return true;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        //这里从0循环到m-1的原因参见上面对于g的叙述
        for (int j = 0; j < m; ++j) {
            int t;
            cin >> t;
            g[i] += !t << j;
        }
    }
    //预处理合法状态
    for (int i = 0; i < 1 << m; ++i)
        if (check(i))
            state.push_back(i);
    //预处理合法状态对
    for (int i = 0; i < state.size(); ++i)
        for (int j = 0; j < state.size(); ++j)
            if ((state[i] & state[j]) == 0)
                head[i].push_back(j);
    
    f[0][0] = 1;
    //这里迭代到n+1的原因参考之前题目，是为了一步出答案
    for (int i = 1; i <= n + 1; ++i) {
        for (int a = 0; a < state.size(); ++a) {
            if (state[a] & g[i]) continue;
            for (auto b: head[a]) {
                f[i][a] = (f[i][a] + f[i - 1][b]) % mod;
            }
        }
    }
    cout << f[n + 1][0] << endl;
    return 0;
}
​```
```

