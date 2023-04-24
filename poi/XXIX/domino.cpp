#include <iostream>
#include <vector>
#include <map>

using namespace std;

const long long MAX_M = 1000000000000000000;
const int inf = 1 << 30;

int Calc(long long m, vector<pair<int, long long>>&fib, map<long long, int>&dp) {
    if(dp[m] != 0)
        return dp[m];
    dp[m] = inf;
    for(auto [len, div] : fib) {
        if(m % div == 0) {
            dp[m] = min(dp[m], Calc(m / div, fib, dp) + len + 1);
        }
    }
    return dp[m];
}

int Solve(long long m, vector<pair<int, long long>>&fib) {
    if(m == 1)
        return 1;
    map<long long, int>dp = {{1, -1}};
    int result = Calc(m, fib, dp);
    return (result == inf) ? 0 : result;
}

int main() {
    ios_base::sync_with_stdio(0);
    
    vector<pair<int, long long>>fib = {make_pair(2, 2), make_pair(3, 3)};
    
    while(fib.back().second + fib[fib.size() - 2].second <= MAX_M) {
        fib.push_back(make_pair(fib.size() + 2, fib.back().second + fib[fib.size() - 2].second));
    }
    
    long long m; cin >> m;
    int result = Solve(m, fib);
    if(result == 0) {
        cout << "NIE\n";
    } else {
        cout << result << '\n';
    }
    
    return 0;
}
