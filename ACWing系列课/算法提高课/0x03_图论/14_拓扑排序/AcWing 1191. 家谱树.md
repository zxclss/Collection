> topsort

```c++
#include <iostream>
#include <cstring>
using namespace std;


const int N = 110, M = N * N / 2;
int n;
int h[N], e[M], ne[M], idx;
int din[N];
int q[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void topsort() {
    int hh = 0, tt = -1;
    for (int i = 1; i <= n; ++i)
        if (din[i] == 0)
            q[++tt] = i;
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            --din[j];
            if (din[j] == 0) q[++tt] = j;
        }
    }
}
int main() {
    memset(h, -1, sizeof h);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int m;
        while (cin >> m, m) {
            add(i, m);
            ++din[m];
        }
    }
    topsort();
    for (int i = 0; i < n; ++i) cout << q[i] << " ";
    cout << endl;
    return 0;
}

```