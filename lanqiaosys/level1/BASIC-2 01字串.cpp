#include <iostream>

using namespace std;

int main() {
    for (int i = 0; i < 1 << 5; ++ i) {
        for (int j = 4; j >= 0; -- j) {
            printf("%d", i >> j & 1);
        }
        puts("");
    }
    return 0;
}
