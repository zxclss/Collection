#include <iostream>

using namespace std;

void get_primes(int n) {
	printf("%d=", n);
	bool is_first = true;
	for (int i = 2; i <= n / i; ++ i) {
		if (n % i == 0) {
			int s = 0;
			while (n % i == 0) n /= i, ++ s;
			if (is_first) is_first = false;
			else printf("*");
			for (int j = 0; j < s; ++ j) {
				if (j) printf("*");
				printf("%d", i);
			}
		}
	}
	if (n > 1) {
		if (!is_first) printf("*");
		printf("%d", n);
	}
	puts("");
}
int main() {
	int l, r;
	cin >> l >> r;
	for (int i = l; i <= r; ++ i) get_primes(i);
	return 0;
}