```c++
#include <iostream>
using namespace std;

const int N = 22;
int n;
string word[N];
int g[N][N];    //g(i,j)表示第i个单词后接第j个单词，的最短公共部分长度
int cnt[N];     //记录每个单词的使用次数
int res;

void dfs(string str, int now) {
    res = max(res, (int)str.size());
    
    ++cnt[now];
    for (int i = 0; i < n; ++i) {
        //搜寻合法的接龙
        if (g[now][i] && cnt[i] < 2) {
            dfs(str + word[i].substr(g[now][i]), i);
        }
    }
    --cnt[now];
}
int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> word[i];
    string ch;  //开始字母
    cin >> ch;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            const string &a = word[i], &b = word[j];
            for (int len = 1; len < a.size() && len < b.size(); ++len) {
                if (a.substr(a.size() - len) == b.substr(0, len)) {
                    g[i][j] = len;
                    break;
                }
            }
        }
    }
    
    for (int i = 0; i < n; ++i)
        if (word[i].substr(0, 1) == ch)
            dfs(word[i], i);    //搜寻合法的开始单词，然后接龙
    
    cout << res << endl;
    return 0;
}

```

