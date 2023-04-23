#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <cstring>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    if(n < 100) {
        printf("%d\n", n % 10);
    } else {
        int smallA = 10, smallB = 10;
        while(n) {
            int x = n % 10;
            if(x <= smallA) {
                smallB = smallA;
                smallA = x;
            } else if(x < smallB)
                smallB = x;
            n /= 10;
        }
        printf("%d\n", smallA);
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
