#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    long long n, k; cin >> n >> k;
    vector<long long>v(n);
    for(long long &x : v)
        cin >> x;
    long long result = - n * n * n;
    for(long long i = max(0ll, n - 1000); i < n; i++) {
        for(long long j = i + 1; j < n; j++) {
            result = max(result, 1ll * (i + 1) * (j + 1) - k * (v[i] | v[j]));
        }
    }
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
