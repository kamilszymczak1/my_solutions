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
    int n; scanf("%d", &n);
    long long k, b, s1; scanf("%lld%lld%lld", &k, &b, &s1);
    
    long long s2 = b * k;
    
    if(s2 > s1) {
        printf("-1\n");
        return;
    }
    
    long long diff = s1 - s2;
    
    vector<long long>a(n);
    for(int i = 0; i < n; i++) {
        if(diff < k - 1) {
            a[i] = diff;
            diff = 0;
        } else {
            a[i] = k - 1;
            diff -= k - 1;
        }
    }
    
    if(diff != 0) {
        printf("-1\n");
        return;
    }
    
    long long my_sum = 0;
    for(long long x : a)
        my_sum += x;
    
    long long to_go = s1 - my_sum;
    
    if(to_go < 0 || to_go % k != 0) {
        printf("-1\n");
    }
    
    a[0] += to_go;
    
    for(int i = 0; i < n; i++)
        printf("%lld " ,a[i]);
    
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
