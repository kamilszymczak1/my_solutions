#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

#define LSB(x) (x & (-x))

using namespace std;

const long long mod = 1'000'000'007;

void Add(int &a, int b) {
    a += b;
    if(a >= mod)
        a -= mod;
}

struct FenwickTree {
    vector<int>values;
    FenwickTree(int _n) {
        values.resize(_n + 1, 0);
    }
    void AddAtPoint(int x, int value) {
        for(x++; x < (int)values.size(); x += LSB(x))
            Add(values[x], value);
    }
    int PrefixSum(int x) {
        int result = 0;
        for(x++; x; x -= LSB(x))
            Add(result, values[x]);
        return result;
    }
    int Sum(int l, int r) {
        long long result = PrefixSum(r) - (l == 0 ? 0 : PrefixSum(l - 1));
        return result < 0 ? result + mod : result;
    }
};

void Scale(vector<int>v, map<int, int>&m) {
    sort(v.begin(), v.end());
    int id = 0, n = v.size();
    for(int i = 0; i < n; i++) {
        while(i < n - 1 && v[i] == v[i + 1])
            i++;
        m[v[i]] = id++;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<int>v(n + 1, 0), dp(n + 1, 0);
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
        Add(v[i], v[i - 1]);
    }
    map<int, int>m;
    Scale(v, m);
    dp[0] = 1;
    vector<FenwickTree>T(2, FenwickTree(m.size()));
    for(int i = 0; i <= n; i++) {
        int id = m[v[i]];
        Add(dp[i], T[v[i] % 2].Sum(0, id));
        Add(dp[i], T[1 - (v[i] % 2)].Sum(id + 1, (int)m.size() - 1));
        T[v[i] % 2].AddAtPoint(id, dp[i]);
    }
    cout << dp[n] << '\n';
    
    return 0;
}
