```c++
#include <iostream>
#include <cstring>
using namespace std;

// 只有小于k的时候才会进行x2和+1的操作
// 因此整个过程中，最大值是2k
// 我们只需把数组开到数据范围的两倍即可
const int N = 2e5 +10;
int n, k;
int dist[N];
int q[N];

int bfs() {
    memset(dist, -1, sizeof dist);
    dist[n] = 0;

    int hh = 0, tt = 0;
    q[0] = n;

    while (hh <= tt) {
        int t = q[hh++];
        if (t == k) return dist[t];
        //+1操作
        if (t < k && dist[t + 1] == -1) {
            dist[t + 1] = dist[t] + 1;
            q[++tt] = t + 1;
        }
        //x2操作
        if (t < k && dist[2 * t] == -1) {
            dist[2 * t] = dist[t] + 1;
            q[++tt] = 2 * t;
        }
        //-1操作
        if (t > 0 && dist[t - 1] == -1) {
            dist[t - 1] = dist[t] + 1;
            q[++tt] = t - 1;
        }
    }
    return -1;
}
int main() {
    cin >> n >> k;
    cout << bfs() << endl;
    return 0;
}
```

