#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n; cin >> n;
    long long k; cin >> k;
    long long sum = 0;
    vector<long long>a(n);
    for(long long &x : a) {
        cin >> x;
        sum += x;
    }
    if(n == 1) {
        cout << max(0ll, a[0] - k) << '\n';
        return;
    }
    sort(a.begin(), a.end());
    sum -= a[0];
    long long suffixSum = 0;
    long long result = (sum + a[0] - k);
    for(int taken = 1; taken <= n - 1; taken++) {
        suffixSum += a[n - taken];
        long long requiredA0 = (k - sum + suffixSum) / (taken + 1);
        if(k - sum + suffixSum <= 0) {
            if((sum - k - suffixSum) % (taken + 1) != 0)
                requiredA0--;
        }
        result = min(result, max(0ll, a[0] - requiredA0) + taken);
    }
    cout << max(result, 0ll) << '\n';
}


int main() {
    ios_base::sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--) {
        TestCase();
    }
    
    return 0;
}
