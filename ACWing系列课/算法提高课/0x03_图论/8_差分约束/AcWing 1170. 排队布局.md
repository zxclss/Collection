```c++
#include <iostream>
#include <cstring>

using namespace std;

/*
x_i+1 >= x_i    -> x_i <= x_i+1
x_b - x_a <= L  -> x_b <= x_a + L
x_b - x_a >= D  -> x_a <= x_b - D
*/

const int N = 1010, M = 21010, INF = 0x3f3f3f3f;
int n, m1, m2;
int h[N], e[M], w[M], ne[M], idx;
int dist[N], cnt[N], q[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
bool spfa(int size) {
    memset(dist, 0x3f, sizeof dist);
    memset(cnt, 0, sizeof cnt);
    memset(st, 0, sizeof st);
    
    int hh = 0, tt = 0;
    for (int i = 1; i <= size; ++i) {
        q[tt++] = i;
        dist[i] = 0;
        st[i] = true;
    }
    
    while (tt != hh) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;
        
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                
                if (cnt[j] >= n) return false;
                
                if (!st[j]) {
                    st[j] = true;
                    q[tt++] = j;
                    if (tt == N) tt = 0;
                }
            }
        }
    }
    return true;
}
int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m1 >> m2;
    for (int i = 1; i <= n; ++i) add(i, i - 1, 0);
    while(m1--) {
        int a, b, L;
        cin >> a >> b >> L;
        add(a, b, L);
    }
    while (m2--) {
        int a, b, D;
        cin >> a >> b >> D;
        add(b, a, -D);
    }
    if (!spfa(n)) puts("-1");
    else {
        spfa(1);
        if (dist[n] > INF / 2) puts("-2");
        else printf("%d\n", dist[n]);
    }
    return 0;
}
```