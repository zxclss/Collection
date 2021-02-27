```c++
#include <iostream>
#include <cstring>

using namespace std;

/*
对于这种区间问题，我们可以想到的几种方法中，前缀和最适用这一题
sum_i表示 1~i 中被我们选出的数的个数
(1)sum_i >= sum_i-1
(2)sum_i - sum_i-1 <= 1     ->      sum_i-1 >= sum_i - 1
(3)sum_bi - sum_ai-1 >= ci    ->      sum_bi >= sum_ai-1 + ci

题目要求最小值，因此我们要求的是不等式链的所有下界的最大值，图论中最远路
*/

const int N = 50010, M = 3 * N;
int n;
int h[N], e[M], w[M], ne[M], idx;
int dist[N], q[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
void spfa() {
    int hh = 0, tt = 1;
    memset(dist, -0x3f, sizeof dist);
    dist[0] = 0;
    q[0] = 0;   //前缀和的递推关系保证了0与所有点相连，0就是超级源点
    
    while (tt != hh) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;
        
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] < dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {
                    st[j] = true;
                    q[tt++] = j;
                    if (tt == N) tt = 0;
                }
            }
        }
    }
    
}
int main() {
    memset(h, -1, sizeof h);
    scanf("%d", &n);
    //(1)和(2)
    for (int i = 1; i < N; ++i) {
        add(i - 1, i, 0);
        //↑这一条加边，会让0得以连接到所有的点，因此0成为了我们的超级源点
        add(i, i - 1, -1);
    }
    //(3)
    while (n--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        ++a, ++b;
        //a和b可能会取0，为了方便做前缀和，防止-1越界，我们把范围全体加1
        //大家都加了1，就相当于大家都没加1，不影响答案
        add(a - 1, b, c);
    }
    spfa();
    printf("%d\n", dist[50001]);
    return 0;
}
```