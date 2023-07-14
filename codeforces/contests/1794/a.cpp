#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void test_case() {
    int n; cin >> n;
    vector<vector<string>>s(n);
    for(int i = 0; i < 2 * n - 2; i++) {
        string t; cin >> t;
        s[t.size()].push_back(t);
    }
    
    for(int i = 1; i <= n - 1; i++) {
        reverse(s[i][0].begin(), s[i][0].end());
        if(s[i][0] != s[i][1]) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        test_case();
    return 0;
}
