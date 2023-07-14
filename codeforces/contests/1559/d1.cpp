#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

struct DSU {
    vector<int>f;
    DSU(int _n) {
        f.resize(_n);
        iota(f.begin(), f.end(), 0);
    }
    int Find(int x) {
        return f[x] == x ? x : f[x] = Find(f[x]);
    }
    void Union(int a, int b) {
        f[Find(a)] = Find(b);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<int>m(2); cin >> m[0] >> m[1];
    vector<DSU>dsu = {DSU(n), DSU(n)};
    for(int i = 0; i < 2; i++) {
        while(m[i]--) {
            int a, b; cin >> a >> b;
            dsu[i].Union(a - 1, b - 1);
        }
    }
    
    vector<pair<int, int>>ans;
    
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(dsu[0].Find(i) != dsu[0].Find(j) && dsu[1].Find(i) != dsu[1].Find(j)) {
                dsu[0].Union(i, j);
                dsu[1].Union(i, j);
                ans.emplace_back(i + 1, j + 1);
            }
        }
    }
    
    cout << ans.size() << '\n';
    for(auto [a, b] : ans)
        cout << a << ' ' << b << '\n';
    
    return 0;
}
