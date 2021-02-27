

```C++
#include <iostream>
using namespace std;

const int N = 1e5 + 10, M = 1e6 + 10;
char s[M], p[N];
int prefix[N];

int main() {
    int n, m;
    cin >> n >> p + 1 >> m >> s + 1;
    //构造prefix table
    for (int i = 2, j = 0; i <= n; ++i) {  //i必须从2开始，i是1的时候前缀为空集
        while (j > 0 && p[i] != p[j + 1]) j = prefix[j];
        if (p[i] == p[j + 1]) ++j;   //如果i为1，此处要加额外判断(j+1<i)，因为前缀是不包括元素本身的
        prefix[i] = j;
    }
    //KMP
    for (int i = 1, j = 0; i <= m; ++i) {
        while (j > 0 && s[i] != p[j + 1]) j = prefix[j];
        if (s[i] == p[j + 1]) ++j;
        if (j == n) {
            printf("%d ", i - j);
            j = prefix[j];
        }
    }
    return 0;
}
```

