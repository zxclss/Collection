#include <iostream>
#include <cstring>

using namespace std;

typedef long long LL;

const int N = 3;
const int mod = 10007;

int n;
int a[N][N] = {1, 0, 0};
int b[N][N] = {
	{1, 1, 1},
	{1, 0, 0},
	{0, 0, 1}
};

void mul(int a[][N], int b[][N], int c[][N]) {
	static int t[N][N];
	memset(t, 0, sizeof t);
	for (int i = 0; i < N; ++ i) {
		for (int j = 0; j < N; ++ j) {
			for (int k = 0; k < N; ++ k) {
				t[i][j] = (t[i][j] + (LL)a[i][k] * b[k][j] % mod) % mod;
			}
		}
	}
	memcpy(c, t, sizeof t);
}
int main() {
	cin >> n;
	while (n) {
		if (n & 1) mul(a, b, a);
		mul(b, b, b);
		n >>= 1;
	}
	cout << a[0][1] << endl;
	return 0;
}