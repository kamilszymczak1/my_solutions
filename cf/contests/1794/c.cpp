#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

void test_case() {
    int n; cin >> n;
    multiset<int, greater<int>>s;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        
        if(s.empty()) {
            s.insert(x);
        } else {
            if(x <= *(--s.end())) {
                if(x >= s.size() + 1) {
                    s.insert(x);
                }
            } else {
                while(!s.empty() && *(--s.end()) < s.size() + 1)
                    s.erase(--s.end());
                s.insert(x);
            }
        }
        
        cout << s.size() << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        test_case();
    return 0;
}
