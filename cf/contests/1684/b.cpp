#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <cstring>

using namespace std;

void TestCase() {
    long long a, b, c; scanf("%lld%lld%lld", &a, &b, &c);
    printf("%lld %lld %lld\n", a + c + b, c + b, c);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
