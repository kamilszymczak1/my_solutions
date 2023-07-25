#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    map<int, vector<int>>m;
    int n, q; cin >> n >> q;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        m[x].push_back(i + 1);
    }
    while(q--) {
        int x, k; cin >> x >> k;
        if(m[x].size() < k) {
            cout << "-1\n";
        } else {
            cout << m[x][k - 1] << '\n';
        }
    }
    
    return 0;
}
