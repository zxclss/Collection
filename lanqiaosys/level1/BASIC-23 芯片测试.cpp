#include <iostream>

using namespace std;

const int N = 25;

int n;
int g[N][N];

bool check(int a, int b) {
	for (int i = 0; i < n; ++ i)
		if (g[a][i] != g[b][i]) return false;
	return true;
}
int main() {
	cin >> n;
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < n; ++ j)
			cin >> g[i][j];
	int res = 0;
	for (int i = 0; i < n; ++ i) {
		if (g[i][i] == 0) continue;
		bool flag = true;
		for (int j = 0; j < n; ++ j) {
			if (g[i][j] == 1 && check(i, j)) {
				flag = false;
				break;
			}
		}
		if (flag) {
			res = i;
			break;
		}
	}
	for (int i = 0; i < n; ++ i)
		if (g[res][i] == 1) 
			cout << i + 1 << " ";
	puts("");
	return 0;
}