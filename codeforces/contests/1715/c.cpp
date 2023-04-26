#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <cassert>
#include <cmath>

using namespace std;

void test_case() {
    long long n, m; scanf("%lld%lld", &n, &m);
    
    vector<long long>weight(n - 1);
    for(long long i = 0; i < n - 1; i++) {
        weight[i] = 1ll * (i + 1) * (n - i - 1);
    }
    
    vector<int>a(n);
    for(int &x : a)
        scanf("%d", &x);
    
    long long result = 1ll * n * (n + 1) / 2;
    
    for(int i = 0; i < n - 1; i++) {
        if(a[i] != a[i + 1]) {
            result += weight[i];
        }
    }
    
    while(m--) {
        int i, x; scanf("%d%d", &i, &x); i--;
        
        if(i != n - 1) {
            if(a[i] != a[i + 1])
                result -= weight[i];
        }
        
        if(i != 0) {
            if(a[i] != a[i - 1])
                result -= weight[i - 1];
        }
        
        a[i] = x;
        
        if(i != n - 1) {
            if(a[i] != a[i + 1])
                result += weight[i];
        }
        
        if(i != 0) {
            if(a[i] != a[i - 1])
                result += weight[i - 1];
        }
        
        printf("%lld\n", result);
    }
}

int main() {
    int t = 1;
    while(t--)
        test_case();
    return 0;
}
