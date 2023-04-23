#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <bitset>
#include <queue>
#include <stack>
#include <cmath>
#include <cstring>

using namespace std;

void test_case() {
    int n, k; scanf("%d%d", &n, &k);
    
    vector<long long>a(n);
    long long answer = 0;
    for(int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    
    for(int j = 0; j < k; j++) {
        long long hi = 0;
        for(int i = 0; i * k + j < n; i++) {
            hi = max(hi, a[i * k + j]);
        }
        answer += hi;
    }
    printf("%lld\n", answer);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
