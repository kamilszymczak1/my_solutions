#include <iostream>
    
using namespace std;
    
int main() {
    long long a, x, b, y; cin >> a >> x >> b >> y;
    long long t; cin >> t;
    
    long long X = max(0ll, t - 30) * x;
    long long Y = max(0ll, t - 45) * y;
    
    cout << 21 * X + a << ' ' << 21 * Y + b << '\n';
    
    return 0;
}
