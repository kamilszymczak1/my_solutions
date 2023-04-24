#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int inf = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<int>dp(3, inf), newDp(3);
    int x; cin >> x;
    dp[x + 1] = 0;
    for(int i = 1; i < n; i++) {
        newDp[0] = newDp[1] = newDp[2] = inf;
        cin >> x;
        if(x == -1) {
            newDp[0] = dp[0];
            newDp[2] = dp[2] + 2;
        }
        if(x == 0) {
            newDp[0] = dp[0] + 1;
            newDp[1] = min(dp[0], dp[1]);
            newDp[2] = dp[2] + 1;
        }
        if(x == 1) {
            newDp[0] = dp[0] + 2;
            newDp[1] = dp[0] + 1;
            newDp[2] = min(dp[0], min(dp[1], dp[2]));
        }
        swap(dp, newDp);
    }
    
    int result = min({dp[0], dp[1], dp[2]});
    if(result == inf) {
        cout << "BRAK\n";
    } else {
        cout << result << '\n';
    }
}
