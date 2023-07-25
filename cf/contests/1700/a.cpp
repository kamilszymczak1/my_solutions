#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <bitset>

using namespace std;

void TestCase() {
    long long n, m; scanf("%lld%lld", &n, &m);
    
    long long a = m * (m - 1) / 2;
    long long b = m * n * (n + 1) / 2;
    printf("%lld\n", a + b);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
