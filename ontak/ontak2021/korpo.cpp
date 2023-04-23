#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

struct BinomCalculator {
    vector<long double>factorial;
    vector<vector<long double>>binom;
    BinomCalculator(int _n) { 
        factorial.resize(_n + 1, 1);
        for(int i = 1; i <= _n; i++)
            factorial[i] = factorial[i - 1] * i;
        binom.resize(_n + 1);
        binom[0] = {1};
        for(int i = 1; i <= _n; i++) {
            binom[i].resize(i + 1);
            binom[i][0] = 1;
            for(int j = 1; j < i; j++)
                binom[i][j] = binom[i - 1][j] + binom[i - 1][j - 1];
            binom[i][i] = 1;
        }
    }
    long double Get(int n, int k) {
        long double result = 1;
        k = max(k, n - k);
        for(int i = 0; i < n - k; i++)
            result *= (long double)(n - i) / (n - k - i);
        return result;
    }
    long double GetFactorial(int x) {
        return factorial[x];
    }
};

void DFS(int x, int games, vector<vector<long double>>&dp, BinomCalculator &bc, string &decision) {
    if(games == 0) {
        dp[x] = {0};
        return;
    }
    
    const int subtreeGames = (games - 1) / 2;
    const int left = x * 2 + 1;
    const int right = x * 2 + 2;
    
    DFS(left, subtreeGames, dp, bc, decision);
    DFS(right, subtreeGames, dp, bc, decision);
    
    if(decision[left] != decision[x]) {
        for(long double &value : dp[left])
            value = bc.GetFactorial(subtreeGames) - value;
    }
    if(decision[right] != decision[x]) {
        for(long double &value : dp[right])
            value = bc.GetFactorial(subtreeGames) - value;
    }
    
    dp[x].resize(games + 1, 0);
    for(int first = 0; first <= subtreeGames; first++) {
        for(int second = 0; second <= subtreeGames; second++) {
            long double count = dp[left][first] * dp[right][second];
            count *= bc.Get(first + second, first) * bc.Get(games - first - second - 1, subtreeGames - second);
            dp[x][first + second + 1] += count;
        }
    }
    for(int i = 1; i <= games; i++)
        dp[x][i] += dp[x][i - 1];
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    string decision; cin >> decision;
    BinomCalculator bc(1 << (n - 1));
    
    vector<vector<long double>>dp((1 << n) - 1);
    
    DFS(0, (1 << (n - 1)) - 1, dp, bc, decision);
    
    long double result = dp[0].back() / bc.GetFactorial((1 << (n - 1)) - 1);
    
    if(decision[0] == 'A')
        result = 1 - result;
    
    cout << fixed << setprecision(10) << result << '\n';
    
    
    return 0;
}
