#include <iostream>

using namespace std;

const int N = 10;

int n, res;
int g[N][N];
int row[N];
bool col1[N], deg1[2 * N], edeg1[2 * N];
bool col2[N], deg2[2 * N], edeg2[2 * N];

void dfs(int u)
{
	if (u == n)
	{
		++ res;
		return;
	}
	for (int i = 0; i < n; ++ i)
	{
		if (col1[i] || deg1[u - i + n] || edeg1[i + u]) continue;
		if (g[u][i] == 0) continue;
		col1[i] = deg1[u - i + n] = edeg1[i + u] = true;
		g[u][i] = 0;
		for (int j = 0; j < n; ++ j)
		{
			if (col2[j] || deg2[u - j + n] || edeg2[j + u]) continue;
			if (g[u][j] == 0) continue;
			col2[j] = deg2[u - j + n] = edeg2[j + u] = true;
			dfs(u + 1);
			col2[j] = deg2[u - j + n] = edeg2[j + u] = false;
		}
		g[u][i] = 1;
		col1[i] = deg1[u - i + n] = edeg1[i + u] = false;
	}
}
int main()
{
	cin >> n;
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < n; ++ j)
			cin >> g[i][j];
	dfs(0);
	cout << res << endl;
	return 0;
}