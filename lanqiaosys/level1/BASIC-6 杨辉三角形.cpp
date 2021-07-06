#include <iostream>

using namespace std;

const int N = 1e5 + 10;

int n;
int f[2][N];

int main() {
	cin >> n;
	f[1][1] = 1;
	cout << f[1][1] << endl;
	for (int i = 2; i <= n; ++ i) {
		for (int j = 1; j <= i; ++ j) {
			f[i & 1][j] = f[i - 1 & 1][j - 1] + f[i - 1 & 1][j];
			cout << f[i & 1][j] << " ";
		}
		cout << endl;
	}
	return 0;
}