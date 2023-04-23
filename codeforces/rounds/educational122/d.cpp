#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase(vector<int>&dist) {
    int n, k; cin >> n >> k;
    vector<int>b(n), c(n);
    int cSum = 0;
    for(auto &x : b)
        cin >> x;
    for(auto &x : c) {
        cin >> x;
        cSum += x;
    }
        
    
    if(k >= 14 * n) {
        cout << cSum << '\n';
        return;
    }
    
    vector<int>dp(k + 1, -1);
    dp[0] = 0;
    for(int i = 0; i < n; i++) {
        int C = c[i], K = dist[b[i]];
      //  cout << "K = " << K << '\n';
        for(int j = k - K; j >= 0; j--) {
            if(dp[j] != -1) {
                dp[j + K] = max(dp[j + K], dp[j] + C);
            }
        }
    }
    int result = 0;
    for(int i = 0; i <= k; i++)
        result = max(result, dp[i]);
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    vector<int>dist(1001, 1 << 30);
    dist[1] = 0;
    for(int i = 1; i <= 1000; i++){ 
        for(int x = 1; x <= i; x++) {
            if(i + i / x <= 1000) {
                dist[i + i / x] = min(dist[i + i / x], dist[i] + 1);
            }
        }
    }
    int t; cin >> t;
    while(t--)
        TestCase(dist);
    return 0;
}
