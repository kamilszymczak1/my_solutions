#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long inf = 1ll << 60;

void TestCase() {
    int n; cin >> n;
    vector<int>a(n), b(n);
    long long T = 0;
    for(auto &x : a) {
        cin >> x;
        T += x * x * (n - 1);
    }
    for(auto &x : b) {
        cin >> x;
        T += x * x * (n - 1);
    }
    vector<long long>dp(n * 100 + 1, inf);
    dp[0] = 0;
    long long sum = 0;
    for(int i = 0; i < n; i++) {
        vector<long long>newDp(n * 100 + 1, inf);
        for(int s = 0; s <= n * 100; s++) {
            if(dp[s] == inf)
                continue;
            long long aSum = s, bSum = sum - s;
            //we do not swap anything
            if(s + a[i] <= n * 100) {
                long long x = dp[s] + a[i] * aSum + b[i] * bSum;
                newDp[s + a[i]] = min(newDp[s + a[i]], x);
            }
            if(s + b[i] <= n * 100) {
                long long x = dp[s] + a[i] * bSum + b[i] * aSum;
                newDp[s + b[i]] = min(newDp[s + b[i]], x);
            }
        }
        sum += a[i] + b[i];
        swap(dp, newDp);
    }
    long long result = inf;
    for(int i = 0; i <= n * 100; i++)
        result = min(result, T + 2 * dp[i]);
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
