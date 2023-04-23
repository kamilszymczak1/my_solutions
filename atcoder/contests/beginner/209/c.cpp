#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    const long long mod = 1e9 + 7;
    
    int n; cin >> n;
    vector<int>c(n);
    for(int &x : c)
        cin >> x;
    sort(c.begin(), c.end());
    
    long long result = c[0];
    
    for(int i = 1; i < n; i++) {
        result *= max(0, c[i] - i);
        result %= mod;
    }
    
    cout << result << '\n';
    
    
    return 0;
}
