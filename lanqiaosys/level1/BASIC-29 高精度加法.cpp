#include <iostream>
#include <cstring>

using namespace std;

const int N = 110;

int al, bl, cl;
int a[N], b[N], c[N];
char s[N];

void add(int a[], int b[], int c[]) {
	int t = 0;
	for (int i = 0; i < al || i < bl; ++ i) {
		if (i < al) t += a[i];
		if (i < bl) t += b[i];
		c[cl ++ ] = t % 10;
		t /= 10;
	}
	if (t) c[cl ++ ] = t;
}
int main() {
	cin >> s;
	for (int i = strlen(s) - 1; i >= 0; -- i) a[al ++ ] = s[i] - '0';
	cin >> s;
	for (int i = strlen(s) - 1; i >= 0; -- i) b[bl ++ ] = s[i] - '0';
	add(a, b, c);
	for (int i = cl - 1; i >= 0; -- i) cout << c[i];
	cout << endl;
	return 0;
}
