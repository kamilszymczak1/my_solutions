#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int Ask(int index) {
    cout << "? " << index + 1 << '\n' << flush;
    int x; cin >> x;
    return x - 1;
}

void TestCase() {
    int n; cin >> n;
    vector<int>ans(n, -1);
    vector<bool>appeared(n + 1, false);
    for(int i = 0; i < n; i++) {
        if(ans[i] == -1) {
            vector<int>values;
            int value = n;
            do {
                appeared[value] = true;
                value = Ask(i);
                values.push_back(value);
            } while(!appeared[value]);
            for(int i = 0; i < (int)values.size() - 1; i++) {
                ans[values[i]] = values[i + 1];
            }
        }
    }
    cout << "! " << flush;
    for(int i = 0; i < n; i++) {
        cout << ans[i] + 1 << ' ';
    }
    cout << '\n' << flush;
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
