##### 考虑枚举“1 $\leq$ XXXxYYY $\leq$ abcdefg”的问题

##### x是统计第i位上为x的个数

## 1、$n \ne 0$时：

### (1)$XXX < abc$时：

##### 		i)、(000～abc-1) n (000~999)

### (2)$XXX = abc$时：      

##### 		i)、$0 < n < d$时：abc n (000~999)

##### 		ii)、$d < n \leq 9$时：不存在

##### 		iii)、$n = d$时：abc n (000~efg)

## 2、$n = 0$时：

### 	(1)$XXX < abc$时：(001~abc-1)0(000~999)

### 	(2)$XXX = abc$时：与$n \ne 0$的情况保持一致

## 3、考虑边界问题：

### 	(1)i为最高位时$nYYYYYY$：

##### 		i)、$0 < n < d$时：n (000~999999)

##### 		ii)、$d < n \leq 9$时：不存在

##### 		iii)、$n = d$时：n (000~abcefg)







-----------------------------

# 综上所述，可以把逻辑归纳为以下情形

## i不是最高位时(统计XXXxYYY，且XXX < abc的情况)：

##### 	`res += (abc) * 10^i`(统计的情况是(000~abc-1)x(000~999))

##### 	如果统计的x=0，则`res -= 10^i`(x等于0的情况统计的是(001~abc-1)0(000~999), 所以单独减去一个倍数)

## 统一计算(统计abcxYYY的情况)：

##### 	如果`x < num[i]`: `res += 10^i`(统计的是abcx(000~999)的情况)

##### 	如果`x = d`: `res += efg + 1` (统计的是abcx(000~efg)的情况)

##### 	如果`x > d`: 不统计





## 实现代码：

```c++
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

int get_num(vector<int>& num, int l, int r) {
    int res = 0;
    while (l <= r) {
        res = res * 10 + num[r--];
    }
    return res;
}
int count(int n, int x) {
    if (!n) return 0;  //特判 1 ～ 0 计数为 0
    vector<int> num;   //用于存储每一数位上的数字，方便后续使用
    while(n) {
        num.push_back(n % 10);
        n /= 10;
    }
    n = num.size();  //n重新用于记录数字的位数
    int res = 0;
    for (int i = n - 1 - !x; i >= 0; --i) {  //统计 0 的时候，最高位不用考虑
        if (i < n - 1) {
            res += get_num(num, i + 1, n - 1) * pow(10, i);
            if (x == 0) res -= pow(10, i);
        }
        if (num[i] > x) res += pow(10, i);
        else if (num[i] == x) res += get_num(num, 0, i - 1) + 1;
    }
    return res;
}
int main() {
    int a, b;
    while (cin >> a >> b, a || b) {
        if (a > b) swap(a, b);
        for (int i = 0; i < 10; ++i) {
            cout << count(b, i) - count(a - 1, i) << " ";
        }
        puts("");
    }
    return 0;
}

```