```c++
#include <iostream>
using namespace std;

const int N = 15;
int n;
int a[N];
int group[N][N];
bool st[N];
int res;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
bool check(int list[], int n, int x) {
    for (int i = 0; i < n; ++i)
        if (gcd(x, list[i]) > 1)
            return false;
    return true;
}
//start实际上是一个剪枝，如果当前能找到，那就顺着这个元素继续往后找
//没找到再额外开一个组，从头开始找
void dfs(int group_cnt, int elem_cnt, int u, int start) {
    if (group_cnt >= res) return;
    if (u == n) res = group_cnt;
    
    bool flag = true;
    for (int i = start; i < n; ++i) {
        //当前数字没用过，且与当前组里所有元素互质，就放进去
        if (!st[i] && check(group[group_cnt], elem_cnt, a[i])) {
            st[i] = true;
            group[group_cnt][elem_cnt] = a[i];
            dfs(group_cnt, elem_cnt + 1, u + 1, i);
            st[i] = false;
            flag = false;
        }
    }
    //如果剪枝后没有搜到需要的答案，那么就额外开一个组，从头开始
    if (flag) dfs(group_cnt + 1, 0, u, 0);
}
int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    
    res = n;
    dfs(0, 0, 0, 0);
    cout << res + 1 << endl;	//组的下标从0开始，额外+1修正
    return 0;
}
```

