#include <iostream>
#include <cstring>

using namespace std;

const int N = 35;

int n, m;
int a[N][N];
int b[N][N];

void mul(int a[][N], int b[][N], int c[][N]) {
	static int t[N][N];
	memset(t, 0, sizeof t);
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < n; ++ j) {
			for (int k = 0; k < n; ++ k) {
				t[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	memcpy(c, t, sizeof t);
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; ++ i) {
		a[i][i] = 1;
		for (int j = 0; j < n; ++ j) {
			cin >> b[i][j];
		}
	}
	while (m) {
		if (m & 1) mul(a, b, a);
		mul(b, b, b);
		m >>= 1;
	}
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < n; ++ j) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}