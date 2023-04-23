#include <iostream>
#include <algorithm>
    
using namespace std;
    
int main() {
    ios_base::sync_with_stdio(0);
    long long x, y, z;
    while(cin >> x >> y >> z) {
        long long A = x * y;
        long long B = z - y;
        long long g = __gcd(A, B);
        cout << A / g << "/" << B / g << '\n';
    }
    return 0;
}
