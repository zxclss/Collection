#include <iostream>

using namespace std;

typedef long long LL;

int get(char ch) {
	if (isdigit(ch)) return ch - '0';
	return ch - 'A' + 10;
}
int main() {
	string n;
	LL res = 0;
	cin >> n;
	for (int i = 0; i < n.size(); ++ i) res = res * 16 + get(n[i]);
	cout << res << endl;
	return 0;
}