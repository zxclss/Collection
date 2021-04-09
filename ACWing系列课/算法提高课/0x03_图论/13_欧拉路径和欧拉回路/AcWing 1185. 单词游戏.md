```c++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 27;
int T, n;
int p[N];
bool st[N]; //记录26个英文字母中第i个字母是否存在
int din[N], dout[N];

int find(int u) {
    if (p[u] != u) p[u] = find(p[u]);
    return p[u];
}
int main() {
    char str[1010];
    scanf("%d", &T);
    while (T--) {
        memset(dout, 0, sizeof dout);
        memset(din, 0, sizeof din);
        memset(st, 0, sizeof st);
        for (int i = 0; i < N; ++i) p[i] = i;
        
        scanf("%d", &n);
        while (n--) {
            scanf("%s", str);
            int len = strlen(str);
            int a = str[0] - 'a', b = str[len - 1] - 'a';
            st[a] = st[b] = true; //把字母标记为已用过
            ++dout[a], ++din[b];
            p[find(a)] = find(b);
        }
        bool success = true;
        //判断是否除了起点和终点外，其他点的入度都等于出度
        //起点和终点要么一个出度多1，一个入度多1
        //要么入度出度也相等（这个不在这里判断在后面判断）
        int start = 0, end = 0;
        for (int i = 0; i < N; ++i) {
            if (din[i] != dout[i]) {
                if (din[i] + 1 == dout[i]) ++start;
                else if (din[i] == dout[i] + 1) ++end;
                else {
                    success = false;
                    break;
                }
            }
        }
        //判断起点-终点状态数是否合法
        //入度比出度多1是终点个数，出度比入度多1是起点个数，应该都是1
        //或者起点和终点是一个字母，那么他的出度入度相等，则都是0
        if (success && !(start == 0 && end == 0 || start == 1 && end == 1)) success = false;
        
        //下面是所有边是否连通的判断
        //我们把所有相连的点用并查集存储为一个集合
        //接下来只需判断使用到的点是否都在一个并查集中即可
        //这就是连通性判断
        int represent = -1;
        for (int i = 0; i < N; ++i) {
            if (st[i]) {
                if (represent == -1) represent = find(i);
                else {
                    if (find(i) != represent) {
                        success = false;
                        break;
                    }
                }
            }
        }
        if (success) puts("Ordering is possible.");
        else puts("The door cannot be opened.");
        
    }
}
```