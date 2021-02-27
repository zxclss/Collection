```c++
#include <iostream>

using namespace std;

typedef long long LL;

//a*b 可以看做b个a相加
//这样就可以用到快速幂来计算了
LL qmi(LL a, LL b, LL p) {
    LL res = 0;
    while (b) {
        if (b & 1) res = (res + a) % p;
        a = (a + a) % p;
        b >>= 1;
    }
    return res;
}
int main() {
    LL a, b, p;
    cin >> a >> b >> p;
    cout << qmi(a, b, p) << endl;
    return 0;
}
```