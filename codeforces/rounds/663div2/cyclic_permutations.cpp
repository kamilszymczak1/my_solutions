#include <iostream>

#define MAX_N 1000003

using namespace std;

const int64_t mod = 1000000007;

int main() {
    ios_base::sync_with_stdio(0);
    
    int32_t n;
    cin >> n;
    
    int64_t pow2 = 1;
    int64_t factorial = 1;
    for(int64_t i = 2; i <= n; i++)
        factorial = (factorial * i) % mod;
    
    for(int32_t i = 1; i < n; i++)
        pow2 = (pow2 << 1) % mod;
    
    int64_t result = (factorial + mod - pow2) % mod;
    
    cout << result << "\n";
    
    return 0;
}
