#include <iostream>
#include <vector>

using namespace std;

int flip(int x) {
    return x ^ ((1 << 20) - 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<int>dp1(1 << 20), dp2(1 << 20), x(n);
    for(int i = 0; i < n; i++) {
        cin >> x[i];
        dp1[x[i]]++;
        dp2[flip(x[i])]++;
    }
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < (1 << 20); j++) {
            if(j & (1 << i)) {
                dp1[j] += dp1[j ^ (1 << i)];
                dp2[j] += dp2[j ^ (1 << i)];
            }
        }
    }
    
    for(int i = 0; i < n; i++)
        cout << dp1[x[i]] << ' ' << dp2[flip(x[i])] << ' ' << n - dp1[flip(x[i])] << '\n';
    
    return 0;
}
