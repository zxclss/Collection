#include <iostream>

using namespace std;

bool check(int n) {
	int s = 0, t;
	t = n % 10;
	s += t * t * t;
	t = n / 10 % 10;
	s += t * t * t;
	t = n / 100;
	s += t * t * t;
	return s == n;
}
int main() {
	for (int i = 100; i < 1000; ++ i) {
		if (check(i)) cout << i << endl;
	}
	return 0;
}