#include <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++ i) {
        for (int j = i; j && j > i - m; -- j) printf("%c", j + 'A');
        for (int j = 0; j < m - i; ++ j) printf("%c", j + 'A');
        cout << endl;
    }
    return 0;
}
