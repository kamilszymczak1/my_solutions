#include <iostream>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    multiset<long long>change;
    long long value = 0;
    for(int i = 0; i < n; i++) {
        long long x; cin >> x;
        value += x;
        if(!change.empty()) {
            auto it = change.end();
            it--;
            change.erase(it);
        }
        change.insert(x);
        change.insert(x);
    }
    long long slope = -n, x1 = 0, result = 1ll << 60;
    for(long long x2 : change) {
        value += slope * (x2 - x1);
        x1 = x2;
        slope++;
        result = min(result, value);
    }
    cout << result << '\n';
    
    return 0;
}
