#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

void TestCase() {
    long long n; scanf("%lld", &n);
    printf("%lld\n", (1ll << n) - 1);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
