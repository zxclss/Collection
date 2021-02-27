> Floyd解决传递闭包问题
```c++
#include <iostream>
#include <cstring>
using namespace std;

const int N = 27;
int n, m;
int g[N][N], dist[N][N];
bool st[N];

void floyd() {
    //若i<k, k<j，则i<j
    memcpy(dist, g, sizeof g);
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                dist[i][j] |= dist[i][k] && dist[k][j];
}
int check() {
    //不能出现A<A的情况
    //矛盾情况输出2
    for (int i = 0; i < n; ++i)
        if (dist[i][i]) return 2;
    //还有i和j的关系没有确定
    for (int i = 0; i < n; ++i)
        for (int j = 0; j< i; ++j)
            if (!dist[i][j] && !dist[j][i] )
                return 0;
    //所有字母的关系都确定了，输出1
    return 1;
}
char get_min() {
    for (int i = 0; i < n; ++i) {
        if (!st[i]) {
            int flag = true;
            for (int j = 0; j < n; ++j) {
                //这里st[j]是要按照拓扑序，把前面输出的点给去掉
                if (!st[j] && dist[j][i]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                st[i] = true;
                return 'A' + i;
            }
        }
    }
}
int main() {
    while (~scanf("%d%d", &n, &m), n || m) {
        memset(g, 0, sizeof g);
        memset(st, 0, sizeof st);
        char str[4];
        int state = 0, it;
        for (int i = 1; i <= m; ++i) {
            scanf("%s", str);
            int a = str[0] - 'A', b = str[2] - 'A';
            
            if (!state) {
                g[a][b] = 1;
                floyd();
                state = check();
                if (state) it = i;
            }
        }
        if (state == 0) puts("Sorted sequence cannot be determined.");
        else if (state == 2) printf("Inconsistency found after %d relations.\n", it);
        else {
            //从小到大输出
            printf("Sorted sequence determined after %d relations: ", it);
            for (int i = 0; i < n; ++i) printf("%c", get_min());
            printf(".\n");
        }
    }
    return 0;
}
```
### 增量优化
> 因为每次只会额外加进来一条边
> 所有不用每次都从头做一遍floyd
> 可以只更新和新边相关的其他边
```c++
#include <iostream>
#include <cstring>
using namespace std;

const int N = 27;
int n, m;
int dist[N][N];
bool st[N];

int check() {
    //不能出现A<A的情况
    //矛盾情况输出2
    for (int i = 0; i < n; ++i)
        if (dist[i][i]) return 2;
    //还有i和j的关系没有确定
    for (int i = 0; i < n; ++i)
        for (int j = 0; j< i; ++j)
            if (!dist[i][j] && !dist[j][i] )
                return 0;
    //所有字母的关系都确定了，输出1
    return 1;
}
char get_min() {
    for (int i = 0; i < n; ++i) {
        if (!st[i]) {
            int flag = true;
            for (int j = 0; j < n; ++j) {
                //这里st[j]是要按照拓扑序，把前面输出的点给去掉
                if (!st[j] && dist[j][i]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                st[i] = true;
                return 'A' + i;
            }
        }
    }
}
int main() {
    while (~scanf("%d%d", &n, &m), n || m) {
        memset(dist, 0, sizeof dist);
        memset(st, 0, sizeof st);
        char str[4];
        int state = 0, it;
        for (int i = 1; i <= m; ++i) {
            scanf("%s", str);
            int a = str[0] - 'A', b = str[2] - 'A';
            
            if (!state) {
                dist[a][b] = 1;
                
                //因为dist[i][i]=0，是不合法的，所以可能导致
                //j==b的时候没有更新i   但i -> a -> b/j 是合法的
                //i==a的时候没有更新j   但i/a -> b -> j 是合法的
                for (int i = 0; i < n; ++i) {
                    if (dist[i][a]) dist[i][b] = 1;
                    for (int j = 0; j < n; ++j) {
                        if (dist[b][j]) dist[a][j] = 1;
                        dist[i][j] |= dist[i][a] && dist[b][j];
                    }
                }
                state = check();
                if (state) it = i;
            }
        }
        if (state == 0) puts("Sorted sequence cannot be determined.");
        else if (state == 2) printf("Inconsistency found after %d relations.\n", it);
        else {
            //从小到大输出
            printf("Sorted sequence determined after %d relations: ", it);
            for (int i = 0; i < n; ++i) printf("%c", get_min());
            printf(".\n");
        }
    }
    return 0;
}
```