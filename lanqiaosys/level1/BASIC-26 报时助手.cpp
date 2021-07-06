#include <iostream>
// #include <unordered_map>

using namespace std;

// unordered_map<int,string> num = {
// 	{0, "zero"}, {1, "one"}, {2, "two"}, {3, "three"},
// 	{4, "four"}, {5, "five"}, {6, "six"}, {7, "seven"}, 
// 	{8, "eight"}, {9, "nine"}, {10, "ten"}, {11, "eleven"},
// 	{12, "twelve"}, {13, "thirteen"}, {14, "fourteen"}, {15, "fifteen"},
// 	{16, "sixteen"}, {17, "seventeen"}, {18, "eighteen"}, {19, "nineteen"},
// 	{20, "twenty"}, {30, "thirty"}, {40, "forty"}, {50, "fifty"}
// };

string num[60] = {
	"zero", "one", "two", "three", "four", "five", "six", "seven", 
	"eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", 
	"sixteen", "seventeen", "eighteen", "nineteen", "twenty"
};

void work(int a) {
	// if (num.count(a)) cout << num[a] << " ";
	// else {
	// 	int t = a / 10 * 10;
	// 	cout << num[t] << " ";
	// 	cout << num[a % 10] << " ";
	// }
	if (num[a].size()) cout << num[a] << " ";
	else {
		int t = a / 10 * 10;
		cout << num[t] << " " << num[a % 10] << " ";
	}
}
void init() {
	num[30] = "thirty";
	num[40] = "forty";
	num[50] = "fifty";
}
int main() {
	init();
	int a, b;
	cin >> a >> b;
	work(a);
	if (!b) puts("o'clock");
	else work(b);
	puts("");
	return 0;
}