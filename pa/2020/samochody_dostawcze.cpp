#include <algorithm>
#include <iostream>
using namespace std;
const int MAX_N = 500007, T = 1000007;
int c[2][T << 1], taken = 0, n, r, w, t, i;
int main() {
    ios_base::sync_with_stdio(0);
    for(cin >> n, i = 0; i < n; i++) {
        cin >> r >> w >> t;
        int index = w - t + T, pos = r - 1;
        if(c[pos][index] < c[pos ^ 1][index])
            taken++;
        c[pos][index]++;
    }
    cout << taken << '\n';
    return 0;
}
