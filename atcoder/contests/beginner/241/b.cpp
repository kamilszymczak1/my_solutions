#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    multiset<int>s;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        s.insert(x);
    }
    
    for(int i = 0; i < m; i++) {
        int x; cin >> x;
        if(s.find(x) == s.end()) {
            cout << "No\n";
            return 0;
        } else {
            s.erase(s.find(x));
        }
    }
    
    cout << "Yes\n";
    
    return 0;
}
