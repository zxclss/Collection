```c++
#include <iostream>
#include <cstring>
using namespace std;

/*
先设定除最后一个数字外，每个数字 i 的后继为 i + 1 （例如1-2, 2-3, 3-4, i-i+1）
我们每次挪动一个区间的时候，会影响3个数字的后继。举例：把[l,r]移到[x,y]后面
挪动前----- p l ---- r x ------ y ------
挪动后----- p x ------ y l ---- r ------
会影响到后继的数字分别是p, r, y（也就是我们移动一次的情况下最多能够修复3个数的后继）
而对于正确的序列123456...n他的后继正确数为n
而错误的随机序列，假设他的后继正确数为m
每次移动会更改3个后继，则它的至少移动次数为(n - m) / 3上取整
化为下取整的公式就是(n - m + 2) / 3
我们就把他设置为我们的估价函数f(n)
IDA*中，我们的操作数是 >= 估价函数f(n)的，因此如果剩余操作数<f(n)则可以直接剪枝
也就是说在我们迭代加深的时候，如果一次移动之后当前迭代深度depth+当前状态的估价函数f(q)>5，则直接剪枝，即现在采用最优策略，也无法在5次内还原
*/

const int N = 20;
int T, n;
int w[5][N];    //五层深度的备份
int cur[N];

//估价函数f(n)
int f(int cur[]) {
    int cnt = 0;
    //最后一个数不用确定后继
    for (int i = 0; i < n - 1; ++i) {
        if (cur[i + 1] != cur[i] + 1) ++cnt;
    }
    return (cnt + 2) / 3;
}
bool dfs(int depth, int max_depth) {
    if (depth + f(cur) > max_depth) return false; //剪枝
    if (f(cur) == 0) return true;
    
    //枚举交换区间[l,r]的长度
    for (int len = 1; len <= n; ++len) {
        for (int l = 0; l + len - 1 < n; ++l) {
            int r = l + len - 1;
            //枚举插入的位置
            for (int k = r + 1; k < n; ++k) {
                memcpy(w[depth], cur, sizeof cur);  //把当前深度的状态q备份到w[depth]中
                
                //交换操作(双指针)
                int y = l;
                //x在原数组中把[r+1, k]的部分先拷贝到新数组的l后
                for (int x = r + 1; x <= k; ++x, ++y) cur[y] = w[depth][x];
                //x再把原数组中[l, r]的部分接到上面的后面一部分，剩下的保持不动
                for (int x = l; x <= r; ++x, ++y) cur[y] = w[depth][x];
                //交换完成
                
                //drill down
                if (dfs(depth + 1, max_depth)) return true;
                
                memcpy(cur, w[depth], sizeof cur);  //恢复现场
            }
        }
    }
    return false;
    
}
int main() {
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; ++i) cin >> cur[i];
        
        int depth = 0;
        while (depth < 5 && !dfs(0, depth)) ++depth;
        
        if (depth == 5) puts("5 or more");
        else cout << depth << endl;
    }
    return 0;
}

```

