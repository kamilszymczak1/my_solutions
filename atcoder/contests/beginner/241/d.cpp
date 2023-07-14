#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const long long inf = 1ll << 62;

int main() {
    ios_base::sync_with_stdio(0);
    multiset<long long>s;
    for(int i = 0; i < 10; i++) {
        s.insert(-1);
        s.insert(inf);
    }
    int q; cin >> q;
    while(q--) {
        int t; cin >> t;
        if(t == 1) {
            long long x; cin >> x;
            s.insert(x);
        } else if(t == 2) {
            long long x, k; cin >> x >> k;
            auto it = s.upper_bound(x);
            for(int i = 0; i < k; i++)
                it--;
            if(*it < 0 || *it == inf) {
                cout << "-1\n";
            } else {
                cout << *it << '\n';
            }
        } else if(t == 3) {
            long long x, k; cin >> x >> k;
            auto it = s.lower_bound(x);
            for(int i = 0; i < k - 1; i++)
                it++;
            if(*it < 0 || *it == inf) {
                cout << "-1\n";
            } else {
                cout << *it << '\n';
            }
        }
    }
    
    return 0;
}
