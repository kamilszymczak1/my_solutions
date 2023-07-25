#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int inf = 1 << 30;

void TestCase() {
    const int MAX_A = 10007;
    int n, l, K; cin >> n >> l >> K;
    vector<int>a(n), d(n);
    for(auto &x : d)
        cin >> x;
    for(auto &x : a)
        cin >> x;
    
    vector<int>aTwo(a.begin(), a.end());
    sort(aTwo.begin(), aTwo.end());
    vector<int>index(MAX_A, -1);
    for(int i = 0; i < n; i++)
        index[aTwo[i]] = i;
    
    vector<vector<int>>dp(n, vector<int>(K + 1, inf));
    dp[index[a[0]]][0] = 0;
    for(int i = 1; i < n; i++) {
        vector<vector<int>>newDp(n, vector<int>(K + 1, inf));
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < K; k++) {
                newDp[index[a[i]]][k] = min(newDp[index[a[i]]][k], dp[j][k] + (d[i] - d[i - 1]) * aTwo[j]);
                newDp[j][k + 1] = min(newDp[j][k + 1], dp[j][k] + (d[i] - d[i - 1]) * aTwo[j]);
            }
            newDp[index[a[i]]][K] = min(newDp[index[a[i]]][K], dp[j][K] + (d[i] - d[i -1]) * aTwo[j]);
        }
        swap(dp, newDp);
    }
    int result = inf;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= K; j++) {
            result = min(result, dp[i][j] + (l - d[n - 1]) * aTwo[i]);
        }
    }
    if(result == inf) {
        cout << "-1\n";
    } else {
        cout << result << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
