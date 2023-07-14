#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <set>
#include <queue>
#include <map>
#include <stack>
#include <cmath>

using namespace std;

const long long mod = 998244353;

long long mod_pow(long long a, long long x) {
    if(x == 0)
        return 1;
    long long answer = mod_pow(a, x / 2);
    answer = answer * answer % mod;
    if(x % 2 == 1)
        answer = answer * a % mod;
    return answer;
}

long long inv(long long x) {
    return mod_pow(x, mod - 2);
}

void test_case() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    int sum = 0;
    for(int &x : a) {
        scanf("%d", &x);
        sum += x;
    }
    
    int prefix_one = 0;
    for(int i = 0; i < n - sum; i++)
        prefix_one += a[i] == 1;
    
    long long t = (1ll * n * (n - 1) / 2) % mod;
    long long t_inv = inv(t);
    
    long long p = 0;
    
    for(long long x = 1; x <= prefix_one; x++) {
        
        long long k = (x * x % mod) * t_inv % mod;
        long long k_inv = inv(k);
        
        long long l = (k * p % mod) * k_inv % mod;
        long long r = (k * k_inv % mod) * k_inv % mod;
        p = (l + r) % mod;
    }
    
    printf("%lld\n", p);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}

