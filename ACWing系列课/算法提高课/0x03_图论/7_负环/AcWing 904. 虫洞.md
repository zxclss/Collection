```c++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 510, M = 5210;
int T, n, m1, m2;
int h[N], e[M], ne[M], w[M], idx;
int dist[N], cnt[N], q[N];  //cnt用于记录从起点到点i的最短路所使用的边数
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
bool spfa() {
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    memset(cnt, 0, sizeof cnt);
    
    int tt = 0, hh = 0;
    for (int i = 1; i <= n; ++i) {
        q[tt++] = i;
        st[i] = true;
    }
    
    while (tt != hh) {
        int t = q[hh++];
        st[t] = false;
        if (hh == N) hh = 0;
        
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                
                if (cnt[j] >= n) return true;   //最短路边数大于等于n说明存在负环
                
                if (!st[j]) {
                    st[j] = true;
                    q[tt++] = j;
                    if (tt == N) tt = 0;
                }
            }
        }
    }
    return false;
}
int main() {
    scanf("%d", &T);
    while (T--) {
        memset(h, -1, sizeof h);
        idx = 0;    //图论多组测试数据的时候一定要记得把idx初始化为0
        
        scanf("%d%d%d", &n, &m1, &m2);
        while (m1--) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, c), add(b, a, c);
        }
        while (m2--) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, -c);
        }
        if (spfa()) puts("YES");
        else puts("NO");
    }
    
    return 0;
}
```