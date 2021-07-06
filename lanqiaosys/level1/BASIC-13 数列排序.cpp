#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 250;

int n;
int a[N];

void quick_sort(int left, int right) {
    if (left >= right) return;
    int mid = a[left + right >> 1];
    int l = left - 1, r = right + 1;
    while (l < r) {
        do ++ l; while (a[l] < mid);
        do -- r; while (a[r] > mid);
        if (l < r) swap(a[l], a[r]);
    }
    quick_sort(left, r);
    quick_sort(r + 1, right);
}
int main() {
    cin >> n;
    for (int i = 0; i < n; ++ i) cin >> a[i];
    quick_sort(0, n - 1);
    for (int i = 0; i < n; ++ i) cout << a[i] << " ";
    return 0;
}