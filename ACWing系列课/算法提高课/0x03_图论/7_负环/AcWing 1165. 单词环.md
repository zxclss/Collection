> 01分数规划 + 新字符串配对建图方式 + trick判负环思路
```c++
#include <iostream>
#include <cstring>

using namespace std;

/*
这也是一个01分数规划问题，具体关于01分数规划问题见前一题题解“观光奶牛”
但是这一题的建图是需要一定技巧的
常规建图：
    把每个字符串看做点，能够配对的时候，在两个字符串之间连一条边
        这样建图符合正常逻辑思维，用点权来代替出边的边权
        但是这一题一共有1e5个字符串，按照上述建图的思路，最坏可能有1e10条边
        会乱爆MLE和TLE，因此需要改进
本题建图：
    这题需要一定的抽象能力，我们把字符串的首两位和末两位看做两个点，把字符串看作一条边
        这样点最多只有26^2个点，而边数也缩减到1e5了

公式推导：
    Sum(f_i) / Sum(1) > mid
    Sum(f_i) - mid * Sum(1) > 0
    Sum(f_i - mid * 1) > 0
*/

const int N = 700, M = 1e5 + 10;
const double eps = 1e-4;
int m;
int h[N], e[M], w[M], ne[M], idx;
double dist[N];
int cnt[N];
int q[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
bool check(double limit) {
    memset(dist, 0, sizeof dist);
    memset(cnt, 0, sizeof cnt);
    memset(st, 0, sizeof st);
    
    int hh = 0, tt = 0;
    for (int i = 0; i < 676; ++i) {
        q[tt++] = i;
        st[i] = true;
    }
    
    int count = 0;
    while (tt != hh) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;
        
        //找正环，要求“最长路”
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] < dist[t] + w[i] - limit) {
                dist[j] = dist[t] + w[i] - limit;
                cnt[j] = cnt[t] + 1;
                
                if (cnt[j] >= n) return true;
                
                //It's a trick
                //在acm赛制比赛里，数据会设置的极限到理论上没有算法可以通过
                //像这种判负环的问题，可以直接得出，所有点被更新到“很多次”，那么他就存在负环
                //这个“很多次”就很讲究了，需要全凭经验，一般是2*n ~ 10*n次
                ++count;
                if (count > 10000) return true;
                
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
    char str[1010];
    while (cin >> m, m) {
        memset(h, -1, sizeof h);
        while (m--) {
            cin >> str;
            int len = strlen(str);
            if (len < 2) continue;
            int a = (str[0] - 'a') * 26 + (str[1] - 'a');
            int b = (str[len - 2] - 'a') * 26 + (str[len - 1] - 'a');
            add(a, b, len);
        }
        
        double l = 0, r = 1000;
        while (r - l > eps) {
            double mid = (l + r) / 2;
            if (check(mid)) l = mid;
            else r = mid;
        }
        if (l - 0 < eps) puts("No solution");
        else printf("%.2lf\n", r);
    }
    return 0;
}


```
