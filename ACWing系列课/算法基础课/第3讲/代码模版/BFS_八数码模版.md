

```C++
#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_map>
using namespace std;

int bfs(string start) {
    string end = "12345678x";
    queue<string> q;
    unordered_map<string, int> h;
    int dx[4] = {1, 0 ,-1, 0};
    int dy[4] = {0, 1, 0, -1};
  
    q.push(start), h[start] = 0;
  
    while (!q.empty()) {
        string t = q.front();
        q.pop();
        if (t == end) {
            return h[t];
        }
        int k = t.find("x"), distance = h[t];
        int kx = k / 3, ky = k % 3;
        for (int i = 0; i < 4; ++i) {
            int x = kx + dx[i], y = ky + dy[i];
            if (x >= 0 && x < 3 && y >= 0 && y < 3) {
                swap(t[k], t[x * 3 + y]);
                if (h.find(t) == h.cend()) {
                    h[t] = distance + 1;
                    q.push(t);
                }
                swap(t[k], t[x * 3 + y]);
            }
        }
    }
    return -1;
}

int main() {
    string start;
    char ch[2];
    for (int i = 0; i < 9; ++i) {
        cin >> ch[0];
        start += ch;
    }
    cout << bfs(start) << endl;
    return 0;
}

```

