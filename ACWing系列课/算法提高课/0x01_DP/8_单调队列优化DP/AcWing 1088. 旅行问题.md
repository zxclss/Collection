```c++
#include <iostream>
#include <cstring>
using namespace std;

typedef long long LL;
const int N = 2e6 + 10;
int n;
int o[N], d[N];
LL s[N];
int q[N], hh, tt;
bool st[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d%d", &o[i], &d[i]);
    
    //顺时针
    for (int i = 1; i <= n; ++i) s[i] = s[i + n] = o[i] - d[i];
    for (int i = 1; i <= 2 * n; ++i) s[i] += s[i - 1];
    hh = 0, tt = -1;
    for (int i = 2 * n; i >= 0; --i) {
        if (hh <= tt && q[hh] > i + n) ++hh;
        //这里要先计算答案再压入队列，因为我们要的是 “队列里的最小值 - s(i-1) < 0 ?”
        //而我们在n-1开始逐渐计算i+1作为起点打答案，在计算i-1的时候，i-1不得入队列
        if (i < n)
            if (s[q[hh]] >= s[i])   //顺时针从后往前做的时候，计算以i为起点走一周时，剪掉的前缀和下标是i-1
                st[i + 1] = true;           //因为s(i)-s(i-1)的意思是表示从i走到i+1的代价，而路线是i->i+1->...->i-1->i
        while (hh <= tt && s[q[tt]] >= s[i]) --tt;//维护一个最小值
        q[++tt] = i;
    }
    
    
    //逆时针
    d[0] = d[n];
    for (int i = 1; i <= n; ++i) s[i] = s[i + n] = o[i] - d[i - 1];
    for (int i = 1; i <= 2 * n; ++i) s[i] += s[i - 1];
    hh = 0, tt = -1;
    for (int i = 1; i <= 2 * n; ++i) {
        if (hh <= tt && q[hh] < i - n) ++hh;
        //“s(i+n) - 队列最大值 > 0 ?”
        if (i > n)
            if (s[q[hh]] <= s[i])
                st[i - n] = true;
        while (hh <= tt && s[q[tt]] <= s[i]) --tt;  //维护一个最大值，计算公式是 "当前值 - 最大值 > 0 ?"
        q[++tt] = i;
    }
    
    for (int i = 1; i <= n; ++i)
        if (st[i]) puts("TAK");
        else puts("NIE");
    
    return 0;
}
```

