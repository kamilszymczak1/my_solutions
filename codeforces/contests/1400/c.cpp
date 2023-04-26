#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    string s; cin >> s;
    int x; cin >> x;
    int n = s.size();
    vector<bool>ans(n, 1);
    for(int i = 0; i < n; i++) {
        if(s[i] == '0') {
            if(i + x < n) {
                ans[i + x] = 0;
            }
            if(i - x >= 0) {
                ans[i - x] = 0;
            }
        }
    }
    bool correct = true;
    for(int i = 0; i < n; i++) {
        if(s[i] == '1') {
            if((i + x >= n || ans[i + x] == 0) && (i - x < 0 || ans[i - x] == 0))
                correct = false;
        }
    }
    
    if(correct) {
        for(int i = 0; i < n; i++)
            cout << ans[i];
        cout << '\n';
    } else {
        cout << "-1\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
