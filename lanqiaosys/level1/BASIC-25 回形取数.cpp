#include <iostream>

using namespace std;

int n, m;

const int N = 210;

int g[N][N];
bool st[N][N];

int d = 0;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < m; ++ j)
			cin >> g[i][j];
	for (int x = 0, y = 0, k = 0, d = 0; k < n * m; ++ k) {
		st[x][y] = true;
		if (k) cout << " ";
		cout << g[x][y];
		int kx = x + dx[d], ky = y + dy[d];
		if (kx < 0 || kx >= n || ky < 0 || ky >= m || st[kx][ky]) {
			d = (d + 1) % 4;
			kx = x + dx[d], ky = y + dy[d];
		}
		x = kx, y = ky;
	}
	cout << endl;
	return 0;
}