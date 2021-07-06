#include <iostream>
#include <vector>

using namespace std;

string num1[10] = {"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
string num2[4] = {"", "shi", "bai", "qian"};
string num3[3] = {"", "wan", "yi"};

bool check(string res) {
	return res.size() >= 5 && res.substr(res.size() - 5) == "ling ";
}
string work(int t) {
	string res;
	vector<int> nums;
	while (t) nums.push_back(t % 10), t /= 10;
	for (int i = nums.size() - 1; i >= 0; -- i) {
		int t = nums[i];
		if (t) res += num1[t] + " ";
		else if (!check(res)) res += "ling ";
		if (t && i) res += num2[i] + " ";
	}
	if (check(res)) res = res.substr(0, res.size() - 5);
	return res;
}
int main() {
	int n;
	cin >> n;
	if (!n) printf("ling");
	else {
		vector<int> nums;
		while (n) nums.push_back(n % 10000), n /= 10000;

		string res;
		for (int i = nums.size() - 1; i >= 0; -- i) {
			int t = nums[i];
			if (res.size() && t < 1000 
				&& !(res.size() >= 5 && res.substr(res.size() - 5) == "ling ")) 
				res += "ling ";
			if (t) res += work(t);
			if (t && i) res += num3[i] + " ";
		}
		while (check(res)) res = res.substr(0, res.size() - 5);
		if (nums.size() > 1 && nums.back() > 9 && res.substr(0, 2) == "yi") res = res.substr(3);
		cout << res << endl;
	}
	return 0;
}