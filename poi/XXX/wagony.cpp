#include <iostream>
#include <vector>

using namespace std;

const unsigned long long inf = -1;

typedef unsigned long long ull;

const int MAX_N = 1'000'007;
const int T = 10'007;
ull dp[MAX_N], ans[MAX_N], pre[MAX_N];

long long ceil(long long x, long long y) {
    if(x % y == 0)
        return x / y;
    return x / y + 1;
}

long long floor(long long x, long long y) {
    return x / y;
}

long long d, a, b;

void get(long long lo, long long hi) {
    
    if(hi < T) {
        for(long long i = lo; i <= hi; i++)
            dp[i - lo] = pre[i];
        return;
    }
    
    long long l_min = ceil(max(2ll, lo - d), 2);
    long long r_max = min(hi - 1, floor(hi + d, 2));
    
    get(l_min, r_max);
    
    fill(ans, ans + hi - lo + 1, inf);
    
    for(long long i = lo; i <= hi; i++) {
        
        long long l = ceil(max(2ll, i - d), 2);
        long long r = min(i - 1, floor(i + d, 2));
        
        for(ull x = l; x <= r; x++) {
            ull y = i - x;
            ull c = (a * (x % 1001) + b * (y % 1001)) % 1001;
            ans[i - lo] = min(ans[i - lo], dp[x - l_min] + dp[y - l_min] + c);
        }
    }
    
    for(long long i = lo; i <= hi; i++)
        dp[i - lo] = ans[i - lo];
}

int main() {
    ios_base::sync_with_stdio(0);
    long long n; cin >> n;
    cin >> d >> a >> b;
    fill(pre, pre + T, inf);
    pre[1] = 0;
    for(long long i = 2; i < T; i++) {
        long long l = ceil(max(2ll, i - d), 2);
        long long r = min(i - 1, floor(i + d, 2));
        for(ull x = l; x <= r; x++) {
            ull y = i - x;
            ull c = (x * a + y * b) % 1001;
            pre[i] = min(pre[i], pre[x] + pre[y] + c);
        }
    }
    get(n, n);
    cout << dp[0] << '\n';
    return 0;
}
