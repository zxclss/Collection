#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

bool check(int n) {
	if (n / 1000 != n % 10) return false;
	if (n / 100 % 10 != n / 10 % 10) return false;
	return true;
}
int main() {
	for (int i = 1000; i < 10000; ++ i) {
		if (check(i)) cout << i << endl;
	}
	return 0;
}