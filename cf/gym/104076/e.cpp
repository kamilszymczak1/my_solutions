#include <iostream>
#include <cassert>
    
using namespace std;
    
long long extended_euclid(long long a, long long b, long long &x, long long &y) {
    if(b == 0) {
        x = 1; y = 0;
        return a;
    }
    
    long long gcd = extended_euclid(b, a % b, x, y);
    
    long long new_x = y;
    long long new_y = x - (a / b) * y;
    x = new_x;
    y = new_y;
    return gcd;
}
    
long long ceil(long long x, long long y) {
    
    if(x % y == 0 || x * y < 0)
        return x / y;
    
    return x / y + 1;
}
    
long long floor(long long x, long long y) {
    if(x % y != 0 && x * y < 0)
        return x / y - 1;
    return x / y;
}
    
void test_case() {
    int k, n; cin >> n >> k;
    
    if(n == k || k % 2 == 0) {
        cout << "YES\n";
        return;
    }
    
    int a = ceil(n, k);
    int b = ceil(n - (k - 1), k);
    
    if(a == b) {
        cout << "NO\n";
        return;
    } else {
        assert(a == b + 1);
        long long x = n - a * k + k;
        long long y = k - x;
        long long new_x = 0, new_y = 0;
        long long gcd = extended_euclid(a, b, new_x, new_y);
        
        int target = n / 2;
        
        if(target % gcd != 0) {
            cout << "NO\n";
            return;
        }
        
        new_x *= target / gcd;
        new_y *= target / gcd;
        
        long long lo = -(1ll << 60);
        long long hi = +(1ll << 60);
        
        lo = max(lo, ceil(-new_x, a - 1));
        hi = min(hi, floor(+new_y, a + 0));
        
        hi = min(hi, floor(x - new_x, a - 1));
        lo = max(lo, ceil(new_y - y, a + 0));
        
        if(lo <= hi) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
    
int main() {
    int t; scanf("%d", &t);
    while(t--) {
        test_case();
    }
    return 0;
}
