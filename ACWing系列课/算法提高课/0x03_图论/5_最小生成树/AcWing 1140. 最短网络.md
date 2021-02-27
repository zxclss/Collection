> Prim裸题
```c++
#include <iostream>
#include <cstring>
using namespace std;

const int N = 110;
int n;
int g[N][N];
int dist[N];
bool st[N];

int prim() {
    int res = 0;
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    
    for (int i = 0; i < n; ++i) {
        int t = -1;
        for (int j = 1; j <= n; ++j)
            if (!st[j] && (t == -1 || dist[j] < dist[t]))
                t = j;
        
        st[t] = true;
        res += dist[t];
        
        for (int j = 1; j <= n; ++j) {
            dist[j] = min(dist[j], g[t][j]);
        }
    }
    return res;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> g[i][j];
    cout << prim() << endl;
    return 0;
}
```

