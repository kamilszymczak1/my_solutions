#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
    
    
using namespace std;
    
long double f(int pref_max, int pref_min, int suff_max, int suff_min, long double t) {
    long double mx = max((long double)pref_max, suff_max * t);
    long double mn = min((long double)pref_min, suff_min * t);
    return mx - mn;
}
    
int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<int>a(n), suff_max(n), suff_min(n);
    for(auto &x : a)
        cin >> x;
    
    suff_max[n - 1] = suff_min[n - 1] = a[n - 1];
    for(int i = n - 2; i >= 0; i--) {
        suff_min[i] = min(suff_min[i + 1], a[i]);
        suff_max[i] = max(suff_max[i + 1], a[i]);
    }
    
    vector<long double>answer(n, 1);
    
    int pref_max = a[0];
    int pref_min = a[0];
    for(int i = 1; i < n; i++) {
        long double lo = 0, hi = 1;
        
        while(hi - lo >= 1e-12) {
            long double mid_l = lo + (hi - lo) / 3.0;
            long double mid_r = lo + (hi - lo) * 2.0 / 3.0;
            
            long double fl = f(pref_max, pref_min, suff_max[i], suff_min[i], mid_l);
            long double fr = f(pref_max, pref_min, suff_max[i], suff_min[i], mid_r);
            
            if(fl > fr) {
                lo = mid_l;
            } else {
                hi = mid_r;
            }
        }
        
        answer[i] = 1 - lo;
        
        pref_max = max(pref_max, a[i]);
        pref_min = min(pref_min, a[i]);
    }
    
    for(long double d : answer)
        cout << fixed << setprecision(10) << d << ' ';
    
    cout << '\n';
    
    return 0;
}
