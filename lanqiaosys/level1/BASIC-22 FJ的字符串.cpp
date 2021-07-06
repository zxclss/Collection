#include <iostream>

using namespace std;

string dfs(int n) {
	if (n == 1) return "A";
	return dfs(n - 1) + (char)(n - 1 + 'A') + dfs(n - 1);
}
int main() {
	int n;
	cin >> n;
	cout << dfs(n) << endl;
	return 0;
}