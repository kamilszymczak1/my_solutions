#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

struct contract {
    int x, w, c;
    contract(int _x, int _w, int _c) : x(_x), w(_w), c(_c) {}
};

bool operator< (contract a, contract b) {
    return a.x < b.x;
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int n, k; cin >> n >> k;
    vector<contract>contracts;
    for(int i = 0; i < n; i++) {
        int x, w, c; cin >> x >> w >> c;
        contracts.emplace_back(x, w, c);
    }
    
    sort(contracts.begin(), contracts.end());
    vector<long double>dp(n);
    long double answer = 0;
    for(int i = 0; i < n; i++) {
        dp[i] = -contracts[i].w;
        
        for(int j = 0; j < i; j++) {
            long double area = 1ll * k * (contracts[i].x - contracts[j].x) * (contracts[i].c + contracts[j].c) / 200.0;
            dp[i] = max(dp[i], dp[j] + area - contracts[i].w);
        }
        answer = max(answer, dp[i]);
    }
    
    cout << fixed << setprecision(9) << answer << '\n';
    return 0;
}
