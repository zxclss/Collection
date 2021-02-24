```c++
/*
      0     1
      2     3
4  5  6  7  8  9  10
      11    12
13 14 15 16 17 18 19
      20    21
      22    23
*/
#include <iostream>
#include <cstring>
using namespace std;

//每一个拉动操作，最多会增加一个重复数字
//因此我们把估价函数f(n)定位中心数字中非高频数的数字个数

const int N = 24;

int op[8][7] = {
    {0, 2, 6, 11, 15, 20, 22},
    {1, 3, 8, 12, 17, 21, 23},
    {10, 9, 8, 7, 6, 5, 4},
    {19, 18, 17, 16, 15, 14, 13},
    {23, 21, 17, 12, 8, 3, 1},
    {22, 20, 15, 11, 6, 2, 0},
    {13, 14, 15, 16, 17, 18, 19},
    {4, 5, 6, 7, 8, 9, 10}
};
int opposite[8] = {5, 4, 7, 6, 1, 0, 3, 2}; //用于存储与当前操作相反的操作下标
//一方面可以剪枝（上一次操作了i，那么这次不能操作opposite[i]，否则上次的操作就无效了）
//一方面可以用于 dfs 回溯后的恢复现场
int center[8] = {6, 7, 8, 12, 17, 16, 15, 11};
int seq[N];
int path[100];

int f() {
    static int sum[4];
    memset(sum, 0, sizeof sum);
    for (int i = 0; i < 8; ++i) ++sum[seq[center[i]]];
    
    int x = 0;
    for (int i = 1; i <= 3; ++i) x = max(x, sum[i]);
    
    return 8 - x;
}
void operate(int x) {
    int t = seq[op[x][0]];
    for (int i = 0; i < 6; ++i) seq[op[x][i]] = seq[op[x][i + 1]];
    seq[op[x][6]] = t;
}
bool dfs(int depth, int max_depth, int last) {
    if (depth + f() > max_depth) return false;
    if (f() == 0) return true;
    
    for (int i = 0; i < 8; ++i) {
        //剪枝，如果反向拉，就又变成了上上层的状态，必定不是最优解
        if (opposite[i] == last) continue;
        operate(i);
        path[depth] = i;
        if (dfs(depth + 1, max_depth, i)) return true;
        operate(opposite[i]);//恢复现场
    }
    return false;
}
int main() {
    while (cin >> seq[0], seq[0]) {
        for (int i = 1; i < 24; ++i) cin >> seq[i];
        
        int depth = 0;
        while (!dfs(0, depth, -1)) ++depth;
        
        if (!depth) printf("No moves needed");
        else {
            for (int i = 0; i < depth; ++i) printf("%c", 'A' + path[i]);
        }
        printf("\n%d\n", seq[6]);
    }
    return 0;
}

```

