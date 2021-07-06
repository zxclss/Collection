#include <iostream>

using namespace std;

string a, b;

int check() {
	int n = a.size(), m = b.size();
	if (n != m) return 1;
	if (a == b) return 2;
	for (int i = 0; i < n; ++ i)
		if (a[i] != b[i] && a[i] + 32 != b[i] && a[i] - 32 != b[i])
			return 4;
	return 3;
}
int main() {
	cin >> a >> b;
	cout << check() << endl;
	return 0;
}