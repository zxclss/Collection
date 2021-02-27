```c++
#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

const int N = 6, INF = 1e9;

int n;
string rule1[N], rule2[N];

int extend(queue<string>& q, unordered_map<string,int>& d1, unordered_map<string,int>& d2, string r1[], string r2[]) {
    for (int k = 0, len = q.size(); k < len; ++k) {
        string t = q.front();
        q.pop();
        
        for (int i = 0; i < t.size(); ++i) {
            for (int j = 0; j < n; ++j) {
                if (t.substr(i, r1[j].size()) == r1[j]) {
                    string trans = t.substr(0, i) + r2[j] + t.substr(i + r1[j].size());
                    if (d1.count(trans)) continue;
                    if (d2.count(trans)) return d1[t] + 1 + d2[trans];
                    d1[trans] = d1[t] + 1;
                    q.push(trans);
                }
            }
        }
    }
    return INF;
}
int bfs(string start, string end) {
    queue<string> qA, qB;
    unordered_map<string, int> distA, distB;
    qA.push(start); distA[start] = 0;
    qB.push(end);   distB[end] = 0;
    
    while (qA.size() && qB.size()) {
        int t;
        if (qA.size() <= qB.size()) t = extend(qA, distA, distB, rule1, rule2);
        else t = extend(qB, distB, distA, rule2, rule1);
        
        if (t <= 10) return t;
    }
    return INF;
}

int main() {
    string start, end;
    cin >> start >> end;
    while (cin >> rule1[n] >> rule2[n]) ++n;
    int t = bfs(start, end);
    if (t < 11) cout << t << endl;
    else puts("NO ANSWER!");
    return 0;
}
```

