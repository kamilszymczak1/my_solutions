#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

long long Query(long long a, long long b) {
    printf("? %lld %lld\n", a, b);
    fflush(stdout);
    long long ans;
    scanf("%lld", &ans);
    return ans;
}

void TestCase() {
    long long x = Query(2, 4) == 2 ? 0 : 1;
    for(int i = 1; i < 30; i++) {
        long long a = (1ll << i) - x;
        long long b = a + (1ll << (i + 1));
        if(Query(a, b) == (1ll << (i + 1)))
            x += 1ll << i;
    }
    printf("! %lld\n", x);
    fflush(stdout);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
