#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector<string>s(n);
    vector<bool>ans(n, false);
    for(int i = 0; i < n; i++)
        cin >> s[i];
    
    int i = 0;
    for(int _t = 0; _t < m; _t++) {
        string t; cin >> t;
        while(s[i] != t)
            i++;
        ans[i] = true;
        i++;
    }
    
    for(int i = 0; i < n; i++) {
        if(ans[i]) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    
    return 0;
}
