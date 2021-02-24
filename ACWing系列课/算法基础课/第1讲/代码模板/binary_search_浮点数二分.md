```C++
bool check(double x) {/* ... */} // 检查x是否满足某种性质

double binary_search_float(double left, double right) {
    const double eps = 1e-6;   // eps 表示精度，取决于题目对精度的要求
    while (right - left > eps) {
        double mid = (left + right) / 2;
        if (check(mid)) right = mid;
        else left = mid;
    }
    return left;
}
```

