#include <iostream>

using namespace std;

const int INF = 0x3f3f3f3f;

int main() {
	int n;
	cin >> n;

	int maxv = -INF, minv = INF, sum = 0;
	while (n -- ) {
		int x;
		cin >> x;
		maxv = max(maxv, x);
		minv = min(minv, x);
		sum += x;
	}
	printf("%d\n%d\n%d\n", maxv, minv, sum);
	return 0;
}