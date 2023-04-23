#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    vector<long long>a(n);
    for(auto &x : a)
        scanf("%lld", &x);
    if(n == 1) {
        printf("%lld\n", a[0]);
        return;
    }
    long long sum = 0;
    for(auto &x : a)
        sum += x;
    sort(a.begin(), a.end());
    if(a[0] < 0 && a.back() < 0) {
        printf("%lld\n", -sum + 2 * a.back());
        return;
    }
    
    if(a[0] >= 0 && a.back() >= 0) {
        printf("%lld\n", sum - 2 * a[0]);
        return;
    }
    
    sum = 0;
    for(auto &x : a)
        sum += abs(x);
    
    printf("%lld\n", sum);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    
    return 0;
}
