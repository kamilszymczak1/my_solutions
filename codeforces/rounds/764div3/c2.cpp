#include <bits/stdc++.h>
#include <chrono>
#include <random>
/* h8 th1s sh1t */
    
using namespace std;
using ll = long long;
using ul = unsigned long long;
using ld = long double;
    
#define eps 1e-9
#define PI 3.14159265358979323846
#define md ll(1e9 + 7)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define inf (1ll << 60)
#define int long long
#define infi (1 << 30)
    
template<typename T1, typename T2> inline bool umx(T1& a, T2 b) { if (a < b) { a = b; return 1; } return 0; }
template<typename T1, typename T2> inline bool umn(T1& a, T2 b) { if (b < a) { a = b; return 1; } return 0; }
    
vector<bool> used;
vector<int> mt;
vector<vector<int>> g;
    
bool dfs(int v) {
    if (used[v])  return false;
    used[v] = true;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (mt[to] == -1 || dfs(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}
    
void solve_one() {
    int n;
    cin >> n;
    mt.resize(n << 1ll, -1);
    used.resize(n << 1ll);
    g.resize(n << 1ll);
    vector<int> a(n); for (auto& x : a) cin >> x;
    for (int i = 0; i < n; i++) {
        while (a[i]) {
            if (a[i] <= n) {
                g[i].push_back(n + a[i] - 1);
            }
            a[i] >>= 1;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (dfs(i)) {
            ans++;
            used.assign(n << 1ll, false);
        }
    }
    cout << (ans == n ? "YES\n" : "NO\n");
    used.clear();
    g.clear();
    mt.clear();
}
    
    
    
signed main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    auto t = 1;
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    cin >> t;
    cout << setprecision(10);
    while (t--) {
        solve_one();
    }
}
