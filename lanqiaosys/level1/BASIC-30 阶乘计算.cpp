#include <iostream>
#include <vector>

using namespace std;

vector<int> a;

void mul(vector<int>& a, int b) 
{
	vector<int> res;
	int t = 0;
	for (int i = 0; i < a.size(); ++ i)
	{
		t += a[i] * b;
		res.push_back(t % 10);
		t /= 10;
	}
	while (t) res.push_back(t % 10), t /= 10;
	a = res;
}
int main() {
	int n;
	cin >> n;
	a.push_back(1);
	for (int i = 1; i <= n; ++ i) mul(a, i);
	for (int i = a.size() - 1; i >= 0; -- i) cout << a[i];
	cout << endl;
	return 0;
}