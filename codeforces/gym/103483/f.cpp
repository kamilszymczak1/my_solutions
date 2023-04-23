#include <iostream>
    
using namespace std;
    
int main() {
    ios_base::sync_with_stdio(0);
    
    
    long long a, b, c, d; cin >> a >> b >> c >> d;
    long long x, y, z; cin >> x >> y >> z;
    
    cout << x * y * z * (a * b + c * d) << '\n';
}
