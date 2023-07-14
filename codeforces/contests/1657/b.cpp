#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

void TestCase() {
    long long n, b, x, y;
    scanf("%lld%lld%lld%lld", &n, &b, &x, &y);
    long long a = 0, sum = 0;
    for(int i = 1; i <= n; i++) {
        if(a + x > b) {
            a -= y;
            sum += a;
        } else {
            a += x;
            sum += a;
        }
    }
    printf("%lld\n", sum);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
