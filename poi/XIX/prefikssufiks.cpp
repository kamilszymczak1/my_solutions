#include <iostream>
#include <vector>

using namespace std;
const int mod = 1000000009, B = 31;
const int MAX_N = 1000007;
string s;
int PI[MAX_N], n, FI[MAX_N];
long long h[MAX_N], powB[MAX_N];
long long GetHash(int a, int l) {
    long long left = (h[a] * powB[l]) % mod;
    return(h[a + l] - left + mod) % mod;
}
void GetFI() {
    FI[n / 2] = 0;
    for(int i = n / 2 - 1; i >= 0; i--) {
        int k = FI[i + 1] + 2;
        while(k > 0 && GetHash(i, k) != GetHash(n - i - k, k)) {
            k--;
        }
        FI[i] = k;
    }
}
void MP() {
    int k = PI[0] = -1;
    for(int i = 1; i <= n; i++) {
        while(k >= 0 && s[i - 1] != s[k])
            k = PI[k];
        PI[i] = ++k;
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> s;
    if(n % 2 == 0)
        s = s.substr(0, n / 2) + char('z' + 2) + s.substr(n / 2, n / 2), n++;
    else
        s[n / 2] = 'z' + 2;
    MP();
    h[0] = 0;
    powB[0] = 1;
    for(int i = 1; i <= n; i++) {
        h[i] = (h[i - 1] * B + s[i - 1] - 'a' + 1) % mod;
        powB[i] = (powB[i - 1] * B) % mod;
    }
    GetFI();
    int result = 0;
    int x = PI[n];
    while(x >= 0) {
        result = max(result, x + FI[x]);
        x = PI[x];
    }
    cout << result << '\n';
    return 0;
}
