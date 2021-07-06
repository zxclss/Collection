#include <iostream>
using namespace std;

const int N = 8010;

int n;
char s[N];
int cnt[26];

int main() {
	cin >> n;
	cin >> s;
	for (int i = 0; i < n; ++ i) ++ cnt[s[i] - 'a'];

	int flag = 0;
	for (int i = 0; i < 26; ++ i)
		if (cnt[i] & 1)
			++ flag;
	if (n & 1 && flag != 1 || (n & 1) == 0 && flag > 0) puts("Impossible");
	else {
		int res = 0, end = n - 1;
		for (int i = 0; i < end; ++ i) {
			for (int j = end; j >= i; -- j) {
				//中间位置的最后再换过去，不然每次向右交换的时候需要额外一次交换才能换回来
				if (i == j) res += n / 2 - i;
				else if (s[i] == s[j]) {
					for (int k = j; k < end; ++ k) {
						swap(s[k], s[k + 1]);
						++ res;
					}
					-- end;
					break;
				}
			}
		}
		cout << res << endl;
	}
	return 0;
}