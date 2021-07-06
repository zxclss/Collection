#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

int n;

void dfs5(int u, int s, int num) {
	if (u == 3) {
		if (n == s) {
			int t = num;
			num = num * 10 + t / 10 % 10;
			num = num * 10 + t / 100;
			cout << num << endl;
		}
		return;
	}
	for (int i = (u == 0); i < 10; ++ i)
		dfs5(u + 1, s + (1 + (u != 2)) * i, num * 10 + i);
}
void dfs6(int u, int s, int num) {
	if (u == 3) {
		if (n == s) {
			int t = num;
			num = num * 10 + t % 10;
			num = num * 10 + t / 10 % 10;
			num = num * 10 + t / 100;
			cout << num << endl;
		}
		return;
	}
	for (int i = (u == 0); i < 10; ++ i) {
		dfs6(u + 1, s + 2 * i, num * 10 + i);
	}
}
int main() {
	cin >> n;
	dfs5(0, 0, 0);
	dfs6(0, 0, 0);
	return 0;
}