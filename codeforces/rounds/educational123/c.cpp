#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void TestCase() {
    int n; cin >> n;
    long long x; cin >> x;
    vector<long long>dp(n + 1, 0), result(n + 1, 0);
    for(int i = 0; i < n; i++) {
        long long a; cin >> a;
        vector<long long>newDp(n + 1, 0);
        for(int j = 0; j <= n; j++) {
            //propagate dp[i]
            //we can increase a by x
            if(j < n)
                newDp[j + 1] = max(newDp[j + 1], dp[j] + a + x);
            newDp[j] = max(newDp[j], dp[j] + a);
        }
        swap(dp, newDp);
        for(int j = 0; j <= n; j++)
            result[j] = max(result[j], dp[j]);
    }
    for(auto x : result)
        cout << x << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
