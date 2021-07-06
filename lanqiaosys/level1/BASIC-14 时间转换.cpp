#include <iostream>

using namespace std;

int main() {
	int ss;
	cin >> ss;
	printf("%01d:%01d:%01d\n", ss / 3600 % 24, ss / 60 % 60, ss % 60);
	return 0;
}