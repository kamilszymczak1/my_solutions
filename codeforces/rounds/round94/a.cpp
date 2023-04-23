#include <iostream>

using namespace std;

int main() {
    long long t = 0;
    for(int i = 1; i < (1 << 23); i++) {
        t += __builtin_popcount(i);
    }
    cout << t << '\n';
}
