#include <cstdio>
#include <vector>

using namespace std;

long long ceil(long long x, long long y) {
    if(x % y == 0)
        return x / y;
    return x / y + 1;
}

void test_case() {
    int n; scanf("%d", &n);
    long long l, r; scanf("%lld%lld", &l, &r);
    vector<int>a(n);
    for(int i = 1; i <= n; i++) {
        //I want this number to be a multiple of i
        //i * k >= l
        //k >= l / k
        long long k = ceil(l, i);
        long long x = k * i;
        if(x <= r) {
            a[i - 1] = x;
        } else {
            printf("NO\n");
            return;
        }
        //
    }
    printf("YES\n");
    for(int x : a)
        printf("%d ", x);
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
