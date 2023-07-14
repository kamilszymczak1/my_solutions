#include <iostream>
#include <vector>
#include <algorithm>
    
using namespace std;
    
int main() {
    ios_base::sync_with_stdio(0);
    int n, q; cin >> n >> q;
    vector<int>a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    sort(a.begin(), a.end());
    a.resize(unique(a.begin(), a.end()) - a.begin());
    n = a.size();
    vector<int>pref(n);
    pref[0] = a[0];
    for(int i = 1; i < n; i++)
        pref[i] = pref[i - 1] + a[i] - a[i - 1] - 1;
    
    for(int i = 0; i < q; i++) {
        int k; cin >> k;
        int ind = lower_bound(pref.begin(), pref.end(), k) - pref.begin();
        
        if(ind == 0) {
            cout << k - 1 << ' ';
        } else {
            cout << a[ind - 1] + k - pref[ind - 1] << ' ';
        }
    }
    
    cout << '\n';
    
    return 0;
}
