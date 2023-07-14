#include <iostream>
#include <cmath>
    
using namespace std;
    
int main() {
    long long n, t, m, x, y; cin >> n >> t >> m >> x >> y;
    
    long double time1 = (long double)m / x;
    long double time2 = (long double)(n - m) / y;
    
    t *= 60;
    
    long double wait_time = time1 + time2 - t;
    
    wait_time = max(wait_time, (long double)0.0) / 60;
    
    cout << (long long)ceil(wait_time) << '\n';
    
    return 0;
}

