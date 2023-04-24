#include <iostream>
#include <vector>

using namespace std;

const long long mod = 1e9 + 7;

bool Possible(vector<int>&h, int &remaining) {
    int n = h.size();
    vector<int>cnt(n + 1);
    for(int &x : h) {
        cnt[x]++;
        if(cnt[x] > 2)
            return false;
    }
    for(int i = 1; i <= n; i++)
        remaining += cnt[i] == 0;
    for(int i = 0; i < n; i++) {
        if(cnt[h[i]] < 2)
            continue;
        if((i < 2 || h[i] != h[i - 2]) && (i + 2 >= n || h[i] != h[i + 2]))
            return false;
    }
    return true;
}

void Add(long long &a, long long b) {
    a = (a + b);
    while(a >= mod)
        a -= mod;
}

long long Factorial(int x) {
    long long result = 1;
    for(int i = 2; i <= x; i++)
        result = (result * i) % mod;
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, remaining = 0; cin >> n;
    vector<int>h(n);
    for(int &x : h)
        cin >> x;
    if(Possible(h, remaining)) {
        vector<long long>dp(4);
        const int LEFTLEFT = 0b00, RIGHTRIGHT = 0b11, LEFTRIGHT = 0b01, RIGHTLEFT = 0b10;
        dp[RIGHTRIGHT] = dp[RIGHTLEFT] = 1;
        for(int i = 2; i < n; i++) {
            vector<long long>newDp(4);
            if(h[i] == h[i - 2]) {
                Add(newDp[RIGHTLEFT], dp[RIGHTRIGHT]);
                Add(newDp[LEFTLEFT], dp[RIGHTLEFT]);
            } else {
                Add(newDp[LEFTLEFT], dp[LEFTLEFT]);
                Add(newDp[RIGHTLEFT], dp[LEFTRIGHT]);
                Add(newDp[LEFTRIGHT], dp[LEFTLEFT] + dp[RIGHTLEFT]);
                Add(newDp[RIGHTRIGHT], dp[LEFTRIGHT] + dp[RIGHTRIGHT]);
            }
            swap(dp, newDp);
        }
        
        long long result = ((dp[LEFTLEFT] + dp[RIGHTLEFT]) * Factorial(remaining)) % mod;
        cout << result << '\n';
        
    } else {
        cout << "0\n"; 
    }
    
    return 0;
}
