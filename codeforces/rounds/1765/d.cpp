#include <iostream>
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
    
    long long answer = *(--s.end());
    long long last = *(--s.end());
    s.erase(--s.end());
    
    while(!s.empty()) {
        auto it = s.upper_bound(m - last);
        if(it == s.begin()) {
            answer += *(--s.end()) + 1;
            last = *(--s.end());
            s.erase(--s.end());
        } else {
            it--;
            answer += *it;
            last = *it;
            s.erase(it);
        }
    }
    
    cout << answer + 1 << '\n';
    
    return 0;
}
