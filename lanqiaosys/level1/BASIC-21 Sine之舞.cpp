#include <iostream>
#include <sstream>

using namespace std;

string tostring(int n) {
	stringstream ssin;
	string s;
	ssin << n;
	ssin >> s;
	return s;
}
string A(int n, int m) {
	if (n == 1) return "sin(" + tostring(m) + ")";
	return "sin(" + tostring(m - n + 1) + ((m - n + 1) & 1 ? "-" : "+") + A(n - 1, m) + ")";
}
string S(int n, int m) {
	if (n == 1) return A(1, 1) + "+" + tostring(m);
	return "(" + S(n - 1, m) + ")" + A(n, n) + "+" + tostring(m + 1 - n);
}
int main() {
	int m;
	cin >> m;
	cout << S(m, m) << endl;
	return 0;
}