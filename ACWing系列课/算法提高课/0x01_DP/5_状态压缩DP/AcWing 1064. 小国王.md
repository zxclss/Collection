```c++
/*
f(i, j, k)状态表示
    集合：摆好了棋盘的前i行，一共摆了j个国王，当前第i层状态是k的方案
    属性：Count方案数
f(i, j, k)状态转移方程
    这一题是对于某一层的状态压缩，因此状态转移方程无非就是从上一层转移到当前层且两层之间合法的"状态对"
    因此，我们需要先预处理出来所有合法的状态对
    （如果在dp的过程中暴力枚举所有的状态，然后检查配对合法，无疑会超时，因为状态数量是指数级别的2^n）
考虑两层的状态如何才能合法配对：
    __  __  __  __  __
   |1 ||0 ||1 ||0 ||0 |
   |__||__||__||__||__|
    __  __  __  __  __
   |0 ||0 ||0 ||0 ||1 |
   |__||__||__||__||__|
首先独立层合法的状态满足的条件: 
    相邻两个格子之间不能放国王(1)
按照题目要求的规则，第i+1层状态需要满足的条件(只考虑第i层和i+1层，从上往下枚举):
    第i层放国王的位置，i+1层放国王必须避开i层国王的位置以及那个位置相邻的位置(2)

根据以上条件，可以总结出一个二进制表达式:
    state(i) & state(i+1) == 0
    state(i) | state(i+1) 不能出现相邻的 1
*/

#include <iostream>
#include <vector>
using namespace std;

typedef long long LL;
const int N = 12, M = 1 << 10, K = 110;
int n, k;
LL f[N][K][M];
int cnt[M];  //负责存储预处理出来的状态对应的1的个数
vector<int> legal_state;   //存储所有的合法状态
vector<int> head[M]; //存储所有合法状态的合法配对状态(人话说就是和i层配对合法的i+1层状态)
//注意这里反过来也是成立的，即head[i]也可以作为legal_state[i]的前驱
//我们这里就是反过来用的，归根到底讲究的是一个合法配对，是一个“无向边”，不在乎谁是i谁是i+1

bool check(int state) {
    for (int i = 0; i < n; ++i)
        //不能出现连续的1
        if ((state >> i) & 1 && (state >> i + 1) & 1)
            return false;
    return true;
}
int count(int state) {
    int res = 0;
    for(int i = 0; i < n; ++i) res += state >> i & 1;
    return res;
}
int main() {
    cin >> n >> k;
    //预处理所有的合法状态
    for (int i = 0; i < 1 << n; ++i) {
        if (check(i)) {
            legal_state.push_back(i);
            cnt[i] = count(i);  //预处理这个状态对应的1个个数
        }
    }
    //根据所有合法的状态，预处理出他的合法配对状态
    for (int i = 0; i < legal_state.size(); ++i)
        for (int j = 0; j < legal_state.size(); ++j)
            if ((legal_state[i] & legal_state[j]) == 0 && check(legal_state[i] | legal_state[j])) 
                //没有连续的1, 且拼在一起合法
                head[i].push_back(j);
                
    //一定一定要注意，我们这里的head[i]存储的是对应legal_state[i]的合法配对状态
    //无论是head[]的索引，以及他所对应的值，都是以下标作为状态的象征，不是直接的状态
    
    //dp
    f[0][0][0] = 1;
    //这里我们直接迭代到n+1，这样最后答案就会直接存储在f[n+1][k][0]里了
    //f[n+1][k][0]的意思是枚举到第n+1行，放了k个棋子，且n+1层无棋子的方案数
    //其正好对应了我们的答案
    //当然也可以只循环到n，只是最后的答案要枚举f[i][k][0~11111...1111]的所有方案
    for (int i = 1; i <= n + 1; ++i) {
        for (int j = 0; j <= k; ++j) {
            for (int u = 0; u < legal_state.size(); ++u) {
                for (int v = 0; v < head[u].size(); ++v) {
                    //l的意思是，当前层枚举到的状态，需要放置l个国王
                    int l = cnt[legal_state[u]];
                    //因此l是不能超过放置国王数量上限的
                    if (j >= l) f[i][j][u] += f[i - 1][j - l][head[u][v]];
                }
            }
        }
    }
    cout << f[n + 1][k][0] << endl;
    return 0;
}

```

