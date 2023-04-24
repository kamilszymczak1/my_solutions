#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

void TestCase() {
    int n; long long x;
    scanf("%d%lld", &n, &x);
    vector<long long>a(n);
    for(int i = 0; i < n; i++)
        scanf("%lld", &a[i]);
    sort(a.begin(), a.end());
    long long result = 0;
    for(int i = 0; i < n; i++) {
        x -= a[i];
        if(x < 0)
            break;
        result += x / (i + 1) + 1;
    }
    printf("%lld\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}

