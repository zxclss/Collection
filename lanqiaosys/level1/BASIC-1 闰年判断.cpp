#include <iostream>
#include <cstring>

using namespace std;

int main() {
    int yy;
    cin >> yy;
    if (yy % 400 == 0 || yy % 100 && yy % 4 == 0) puts("yes");
    else puts("no");
    return 0;
}
