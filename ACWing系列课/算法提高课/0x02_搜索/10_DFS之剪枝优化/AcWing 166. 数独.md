

```c++
#include <iostream>
using namespace std;

const int N = 9, M = 1 << N;
int ones[M], map[M];
char str[100];
int row[N], col[N], cell[3][3];

void init() {
    for (int i = 0; i < N; ++i)
        row[i] = col[i] = (1 << N) - 1;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            cell[i][j] = (1 << N) - 1;
}
void draw(int x, int y, int val, bool is_set) {
    if (is_set) str[x * N + y] = '1' + val;
    else str[x * N + y] = '.';
    
    int v = 1 << val;
    if (!is_set) v = -v;
    row[x] -= v;
    col[y] -= v;
    cell[x / 3][y / 3] -= v;
}
//获得当前空位置上，纵观横竖子方块后，能够填下数字
int get(int x, int y) {
    return row[x] & col[y] & cell[x / 3][y / 3];
}
//返回最后一个1
int lowbit(int state) {
    return state & ~state + 1;
}
bool dfs(int u) {
    if (!u) return true;
    
    //minv和xy负责记录所有的空子里，枚举数量最小的空格子
    int minv = 10;
    int x, y;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            //是否是空位置
            if (str[i * N + j] == '.') {
                //获得当前空位置上，纵观横竖子方块后，能够填下数字
                int state = get(i, j);
                if (ones[state] < minv) {
                    minv = ones[state];
                    x = i, y = j;
                }
            }
        }
    }
    int state = get(x, y);
    for (int i = state; i; i -= lowbit(i)) {
        //从小到大枚举这个位子上的数字的所有合法情况
        int t = map[lowbit(i)];
        draw(x, y, t, true);
        if (dfs(u - 1)) return true;
        draw(x, y, t, false);
    }
    return false;
}
int main() {
    //map负责把二进制的最后一个1转换成对应的下标
    for (int i = 0; i < N; ++i) map[1 << i] = i;
    //ones记录对应状态中还没有填的位置个数（dfs优化，每次遍历分支少的状态）
    for (int i = 0; i < 1 << N; ++i) {
        for (int j = 0; j < N; ++j) {
            ones[i] += i >> j & 1;
        }
    }
    while (cin >> str, str[0] != 'e') {
        init();
        
        //cnt统计的是空位子的数量，也就是dfs的层数
        int cnt = 0;
        //t是字符串的指针
        for (int i = 0, k = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j, ++k) {
                //非'.'表示有数字，就填上
                if (str[k] != '.') {
                    int t = str[k] - '1';
                    draw(i, j, t, true);
                } else ++cnt;
            }
        }
        dfs(cnt);
        
        puts(str);
    }
    return 0;
}
```