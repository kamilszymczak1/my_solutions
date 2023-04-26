#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<int>a;
    vector<bool>appeared(n + 1, false);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(x <= n && !appeared[x]) {
            appeared[x] = true;
        } else {
            a.push_back(x);
        }
    }
    sort(a.begin(), a.end());
    set<int>s;
    for(int i = 1; i <= n; i++) {
        if(!appeared[i])
            s.insert(i);
    }
    
    int cnt = 0;
    while(!a.empty()) {
        int x = a.back();
        int bound = (x - 1) / 2;
        auto it = s.upper_bound(bound);
        if(it != s.begin())
            it--;
        if(it != s.end() && *it <= bound) {
            cnt++;
            s.erase(it);
        } else {
            cout << "-1\n";
            return;
        }
        a.pop_back();
    }
    cout << cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
