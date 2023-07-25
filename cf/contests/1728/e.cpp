#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

long long extended_gcd(long long a, long long b, long long &x, long long &y, long long n) {
    if(a == 0) {
        x = 0;
        y = n / b;
        return b;
    }
    
    long long g = extended_gcd(b % a, a, x, y, n);
    long long new_x = y - (b / a) * x;
    long long new_y = x;
    
    x = new_x;
    y = new_y;
    
    return g;
}

int main() {
    
    int n; scanf("%d", &n);
    vector<long long>diff;
    long long b_sum = 0;
    for(int i = 0; i < n; i++) {
        long long a, b; scanf("%lld%lld", &a, &b);
        b_sum += b;
        diff.push_back(a - b);
    }
    sort(diff.begin(), diff.end(), greater<long long>());
    
    vector<long long>best(1, b_sum);
    for(long long x : diff)
        best.push_back(best.back() + x);
    
    int split = 0;
    for(int i = 0; i < (int)diff.size(); i++) {
        if(diff[i] >= 0) {
            split = i + 1;
        }
    }
    
    int m; scanf("%d", &m);
    
    while(m--) {
        long long x, y; scanf("%lld%lld", &x, &y);
        
        long long a, b;
        
        long long gcd = extended_gcd(x, y, a, b, n);
        
        if(n % gcd != 0) {
            printf("-1\n");
        } else {
            
            
            long long a_shift = y / gcd;
            long long b_shift = x / gcd;
            
            long long k = (split - x * a) / (a_shift * x);
            
            if((split - x * a) < 0 && (a * x - split) % (a_shift * x) != 0)
                k--;
            
            a = a + k * a_shift;
            b = b - k * b_shift;
            
            long long result = -1;
            for(int i = 0; i < 2; i++) {
                if(a >= 0 && b >= 0)
                    result = max(result, best[a * x]);
                a += a_shift;
                b -= b_shift;
            }
            
            printf("%lld\n", result);
            
        }
    }
    
    return 0;
}
