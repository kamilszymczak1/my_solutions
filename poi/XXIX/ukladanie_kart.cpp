#include <iostream>
#include <vector>

using namespace std;

long long Solve(long long n, long long m) {
    vector<long long>factorial(n + 4, 1);
    for(long long i = 2; i <= n + 3; i++)
        factorial[i] = (factorial[i - 1] * i) % m;
    
    long long result = 0;
    
    vector<long long>p(n + 2);
    p[1] = 1;
    long long pSum = 0;
    for(int i = 2; i <= n - 2; i++) {
        p[i] = (pSum + ((n - i + 1) * p[i - 1] % m) + 1) % m;
        pSum = (pSum + p[i - 1]) % m;
    }
    
    for(long long k = 1; k <= n - 2; k++) {
        
        long long x = (factorial[n - k - 1] * n) % m;
        
        long long a = ((n * (n - 1) - k * (k + 1)) / 2) % m;
        long long b = ((n - k - 2) * factorial[n - k - 2]) % m;
        
        long long toAdd = (((x * k) % m) + ((a * b) % m) * n) % m;
        
        result = (result + (toAdd * p[k]) % m) % m;
    }
    
    long long s = ((n - 1) * factorial[n - 1]) % m;
    s = (s * ((n * (n - 1) / 2) % m)) % m;
    
    result = (result + s) % m;
    
    return result;
}


int main() {
    ios_base::sync_with_stdio(0);
    long long n, m; cin >> n >> m;
    cout << Solve(n, m) << '\n';
    
    return 0;
}
