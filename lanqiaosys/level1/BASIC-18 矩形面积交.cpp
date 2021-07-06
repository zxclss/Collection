#include <iostream>

using namespace std;

int main() {
	double x1, y1, x2, y2;
	double x3, y3, x4, y4;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

	if (x1 > x2) swap(x1, x2);
	if (y1 > y2) swap(y1, y2);
	if (x3 > x4) swap(x3, x4);
	if (y3 > y4) swap(y3, y4);

	double x5 = max(x1, x3);
	double x6 = min(x2, x4);
	double y5 = max(y1, y3);
	double y6 = min(y2, y4);

	double res = (x6 - x5) * (y6 - y5);
	//printf("%lf %lf %lf %lf\n", x5, x6, y5, y6);
	if (x6 <= x5 || y6 <= y5) res = 0;

	printf("%.2lf\n", res);
	return 0;
}