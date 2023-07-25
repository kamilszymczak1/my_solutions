#include <iostream>
#include <numeric>
#include <vector>
#include <map>

using namespace std;

const long long mod = 998244353;

struct DSU {
    int n, k;
    vector<int>f, added, size, pendingToAdd;
    vector<vector<int>>dp;
    void Multiply(int a, int b) {
        vector<int>result(k + 1, 0);
        for(int i = 0; i <= min(k, size[a]); i++) {
            for(int j = 0; j <= min(k - i, size[b]); j++) {
                result[i + j] = (result[i + j] + 1ll * dp[a][i] * dp[b][j]) % mod;
            }
        }
        swap(dp[a], result);
    }
    DSU(int _n, int _k) : n(_n), k(_k) {
        f.resize(_n); added.resize(_n, 0); size.resize(_n, 1);
        dp.resize(_n, vector<int>(_k + 1));
        for(int i = 0; i < _n; i++) {
            dp[i][0] = dp[i][1] = 1;
            f[i] = i;
        }
    }
    int Find(int x) {
        return f[x] == x ? x : f[x] = Find(f[x]);
    }
    void Union(int x, int y) {
        x = Find(x); y = Find(y);
        if(x != y) {
            Multiply(y, x);
            f[x] = y;
            size[y] += size[x];
            added[y] += added[x] + 1;
            pendingToAdd.emplace_back(y);
        }
    }
    int Result() {
        dp.push_back(vector<int>(k + 1, 0));
        size.push_back(0);
        dp.back()[0] = 1;
        for(int i = 0; i < n; i++) {
            if(i == Find(i)) {
                Multiply(n, i);
                size[n] += size[i];
            }
        }
        return accumulate(dp.back().begin(), dp.back().end(), 0ll) % mod;
    }
    
    void MoveUp() {
        for(int x : pendingToAdd) {
            if(added[x] + 1 <= k)
                dp[x][added[x] + 1] = (dp[x][added[x] + 1] - 1 + mod) % mod;
            added[x] = 0;
            dp[x][1] = (dp[x][1] + 1) % mod;
        }
        pendingToAdd.clear();
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    int n, m, k; cin >> n >> m >> k;
    map<int, vector<pair<int, int>>>M;
    for(int i = 0; i < m; i++) {
        int x, y, c; cin >> x >> y >> c;
        M[c].emplace_back(x - 1, y - 1);
    }
    
    DSU dsu(n, k);
    
    for(auto [key, vec] : M) {
        for(auto [x, y] : vec)
            dsu.Union(x, y);
        dsu.MoveUp();
    }
    
    cout << dsu.Result() << '\n';
    
    return 0;
}
