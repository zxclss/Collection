#include <iostream>

using namespace std;

int main() {
	int v1, v2, t, s, l;
	cin >> v1 >> v2 >> t >> s >> l;
	int s1 = 0, s2 = 0;

	for (int i = 0; i < l / v2; ++ i) {
		s1 += v1, s2 += v2;
		if (s1 == l) break;
		if (s1 - s2 >= t) s1 -= v1 * s;
	}
	if (s1 == s2) puts("D");
	else if (s1 == l) puts("R");
	else puts("T");
	cout << s2 / v2 << endl;
	return 0;
}