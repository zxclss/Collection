#include <iostream>

using namespace std;

char get(int x) {
	if (x < 10) return x + '0';
	return 'A' + x - 10;
}
int main() {
	string res;
	int n;
	cin >> n;
	if (!n) res = '0';
	while (n) {
		res = get(n % 16) + res;
		n /= 16;
	}
	cout << res << endl;
	return 0;
}