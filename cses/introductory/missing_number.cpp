#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<bool>p(n + 1, false);
    for(int i = 1; i < n; i++) {
        int x; cin >> x;
        p[x] = true;
    }
    int t = 1;
    while(p[t])
        t++;
    cout << t << '\n';
    return 0;
}
