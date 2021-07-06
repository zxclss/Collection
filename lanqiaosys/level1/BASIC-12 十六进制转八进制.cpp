#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

const int N = 1e5 + 10;
int T, n;
char str[N];
int str8[N * 4];
int pow2[3] = {1, 2, 4};
int res[N];

int get(char ch) {
	if (isdigit(ch)) return ch - '0';
	return ch - 'A' + 10;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> T;
	while (T -- ) {
		cin >> str;
		int cnt = 0;
		n = strlen(str);
		//16 -> 2
		for (int i = n - 1; i >= 0; -- i) {
			int t = get(str[i]);
			for (int j = 0; j < 4; ++ j) {
				str8[cnt ++ ] = t & 1;
				t >>= 1;
			}
		}
		//2 -> 8
		int s = 0, r = 0;
		for (int i = 0; i < cnt; ) {
			s += str8[i] * pow2[i % 3];
			if (++ i % 3 == 0) {
				res[r ++ ] = s;
				s = 0;
			}
		}
		if (s) res[r ++ ] = s;
		//去掉前导零
		while (r > 1 && res[r - 1] == 0) -- r;
		//输出答案
		for (int i = r - 1; i >= 0; -- i) cout << res[i];
		cout << endl;
	}
	return 0;
}