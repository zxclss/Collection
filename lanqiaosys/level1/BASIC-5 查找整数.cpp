#include <iostream>

using namespace std;

const int N = 10010;

int n;
int as[N];

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++ i) {
		int x;
		cin >> x;
		if (!as[x]) as[x] = i;
	}
	int x;
	cin >> x;
	
	if (!as[x]) cout << -1 << endl;
	else cout << as[x] << endl;

	return 0;
}