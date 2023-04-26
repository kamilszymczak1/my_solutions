#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <bitset>
#include <map>

using namespace std;

void TestCase() {
    long long n; scanf("%lld", &n);
    if(n <= 3) {
        printf("%d\n", n == 3 ? 3 : 2);
        return;
    }
    long long result = 1 << 30;
    for(int i = 0; i < 3; i++) {
        long long k = 0;
        for(int bit = 15; bit >= 0; bit--) {
            k += 1 << bit;
            long long intersections = 3 * k * k + 2 * i * k + max(0, i - 1);
            long long triangles = intersections * 2;
            if(triangles >= n)
                k -= 1 << bit;
        }
        result = min(result, 3 * (k + 1) + i);
    }
    printf("%lld\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
}
