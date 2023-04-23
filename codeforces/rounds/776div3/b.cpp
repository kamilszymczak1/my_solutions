#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

void TestCase() {
    long long l, r, a; scanf("%lld%lld%lld", &l, &r, &a);
    long long result = r / a + r % a;
    r -= r % a + 1;
    if(r >= l) {
        result = max(result, r / a + r % a);
    }
        
    printf("%lld\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    
    return 0;
}
