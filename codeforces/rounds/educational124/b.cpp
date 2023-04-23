#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const long long m = 1'000'000'000;

void TestCase() {
    long long n; scanf("%lld", &n);
    vector<long long>x(1, 1);
    while(x.size() < n && x.back() <= m)
        x.push_back(x.back() * 3);
    if(x.size() < n || x.back() > m) {
        printf("NO\n");
    } else {
        printf("YES\n");
        for(long long y : x) {
            printf("%lld ", y);
        }
        printf("\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
