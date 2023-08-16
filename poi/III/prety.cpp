#include <iostream>
#include <cmath>

using namespace std;

void test_case() {
    long double l, d; cin >> l >> d;
    
    long double p = l / 2, q = 1e9;
    
    while(q - p >= 1e-9) {
        long double r = (p + q) / 2;
        
        long double alpha = asin(l / (2 * r));
        long double x = 2 * r * alpha;
        
        if(x < l + d) {
            q = r;
        } else {
            p = r;
        }
    }
    
    cout << (int)round(p - sqrt(p * p - (l * l / 4))) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--)
        test_case();
    
    return 0;
}
