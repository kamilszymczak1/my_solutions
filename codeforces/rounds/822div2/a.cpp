#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <cmath>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<long long>a(n);
    for(int i = 0; i < n; i++)
        scanf("%lld", &a[i]);
    sort(a.begin(), a.end());
    long long answer = 1ll << 60;
    for(int i = 0; i + 2 < n; i++) {
        long long x = a[i];
        long long y = a[i + 1];
        long long z = a[i + 2];
        
        answer = min(answer, y - x + z - y);
    }
    printf("%lld\n", answer);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}
