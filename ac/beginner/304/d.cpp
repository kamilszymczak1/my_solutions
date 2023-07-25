#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    int w, h, n; cin >> w >> h >> n;
    
    vector<pair<int, int>>p(n);
    for(auto &[x, y] : p)
        cin >> x >> y;
    
    int A; cin >> A;
    vector<int>a(A);
    for(int &x : a)
        cin >> x;
    
    int B; cin >> B;
    vector<int>b(B);
    for(int &x : b)
        cin >> x;
    
    vector<map<int, int>>cnt(A + 1);
    
    for(auto &[x, y] : p) {
        int l = lower_bound(a.begin(), a.end(), x) - a.begin();
        int r = lower_bound(b.begin(), b.end(), y) - b.begin();
        ++cnt[l][r];
    }
    
    int hi = 0, lo = 1 << 30, size = 0;
    
    for(auto m : cnt) {
        for(auto [x, y] : m) {
            hi = max(hi, y);
            lo = min(lo, y);
        }
        size += m.size();
    }
    
    if(1ll * size < 1ll * (A + 1) * (B + 1))
        lo = 0;
    
    cout << lo << ' ' << hi << '\n';
    
    return 0;
}
