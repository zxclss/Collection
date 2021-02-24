> 100行的 easy 题
```c++
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <queue>

using namespace std;

char g[2][4];
unordered_map<string, int> dist;
unordered_map<string, pair<char, string>> pre;  //记录当前状态的前驱，以及前驱是通过什么操作过来的
queue<string> q;

//为了方便计算，我们编织get和set函数
//作用是对字符串到数组的转换操作
//这样做是为了方便操作
//（其实我们完全可以对着字符串直接操作的hh，但是y总要求我们先转换再操作）
void set(string state) {
    int t = 0;
    for (int i = 0; i < 4; ++i) g[0][i] = state[t++];
    for (int i = 3; i >= 0; --i) g[1][i] = state[t++];
}
string get() {
    string res;
    for (int i = 0; i < 4; ++i) res += g[0][i];
    for (int i = 3; i >= 0; --i) res += g[1][i];
    return res;
}
string move0(string state) {
    set(state);
    for (int i = 0; i < 4; ++i) swap(g[0][i], g[1][i]);
    return get();
}
string move1(string state) {
    set(state);
    char t1 = g[0][3], t2 = g[1][3];
    for (int i = 3; i; --i) g[0][i] = g[0][i - 1], g[1][i] = g[1][i - 1];
    g[0][0] = t1, g[1][0] = t2;
    return get();
}
string move2(string state) {
    set(state);
    char t = g[0][1];
    g[0][1] = g[1][1];
    g[1][1] = g[1][2];
    g[1][2] = g[0][2];
    g[0][2] = t;
    return get();
}
void bfs(string start, string end) {
    if (start == end) return;
    q.push(start);
    while (!q.empty()) {
        string t = q.front();
        q.pop();
        
        string m[3]; //记录当前状态能够分别转换成的3个状态
        m[0] = move0(t);
        m[1] = move1(t);
        m[2] = move2(t);
        
        // for (int i = 0; i < 3; ++i) {
        //     cout << m[i] << endl;
        // }return;
        
        for (int i = 0; i < 3; ++i) {
            auto &temp = m[i];
            if (!dist.count(temp)) {
                dist[temp] = dist[t] + 1;
                pre[temp] = {(char)'A' + i, t};
                
                if (temp == end) return;
                
                q.push(temp);
            }
        }
    }
}
int main() {
    int x;
    string start, end;
    for (int i = 0; i < 8; ++i) {
        cin >> x;
        end += x + '0';
    }
    start = "12345678";
    
    bfs(start, end);
    cout << dist[end] << endl;
    
    string path;
    while (start != end) {
        path += pre[end].first;
        end = pre[end].second;
    }
    reverse(path.begin(), path.end());
    if (path.size()) cout << path << endl;
    return 0;
}
```

