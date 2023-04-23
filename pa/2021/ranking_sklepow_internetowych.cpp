#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<int>pos(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        pos[x - 1] = i;
    }
    
    long long result = 0;
    int l = pos[n - 1], r = pos[n - 1];
    for(int i = 1; i <= n; i += 2) {
        //len is odd
        l = min(l, pos[n - 1 - i / 2]);
        r = max(r, pos[n - 1 - i / 2]);
        result += max(0, min(n - i, l) - max(0, r - i + 1) + 1);
    }
    l = pos[n - 1], r = pos[n - 1];
    for(int i = 2; i <= n; i += 2) {
        l = min(l, pos[n - 1 - i / 2]);
        r = max(r, pos[n - 1 - i / 2]);
        result += max(0, min(n - i, l) - max(0, r - i + 1) + 1);
    }
    
    cout << 2 * n + 1 << ' ' << result << '\n';
    
    return 0;
}
