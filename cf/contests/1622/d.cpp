#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const long long mod = 998244353;

void TestCase() {
    int n, k; cin >> n >> k;
    string s; cin >> s;
    vector<int>ones;
    vector<vector<long long>>choose(n + 1, vector<long long>(n + 1));
    for(int i = 0; i <= n; i++)
        choose[i][0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            choose[i][j] = (choose[i - 1][j - 1] + choose[i - 1][j]) % mod;
        }
    }
    for(int i = 0; i < n; i++) {
        if(s[i] == '1')
            ones.push_back(i);
    }
    if(ones.size() < k || k == 0) {
        cout << "1\n";
        return;
    }
    if(ones.size() == k) {
        cout << choose[n][ones.size()] << '\n';
        return;
    }
    long long result = 0;
    for(int i = 0; i + k <= ones.size(); i++) {
        int l = ones[i], r = ones[i + k - 1];
        int leftLen = r - l;
        while(l > 0 && s[l - 1] == '0') {
            leftLen++;
            l--;
        }
        int rightLen = 1;
        while(r < n - 1 && s[r + 1] == '0') {
            r++;
            rightLen++;
        }
        
        if(i == 0) {
            result = (result + choose[rightLen + leftLen][k]) % mod;
        } else {
            for(int rightOnes = max(0, k - leftLen); rightOnes <= min(rightLen, k); rightOnes++) {
                if(rightOnes == 1) {
                    result = (result + (rightLen - 1) * choose[leftLen][k - 1]) % mod;
                } else {
                    result = (result + choose[rightLen][rightOnes] * choose[leftLen][k - rightOnes]) % mod;
                }
            }
        }
        
        
    }
    cout << result << '\n';
}


int main() {
    ios_base::sync_with_stdio(0);
    
    int t = 1;
    while(t--) {
        TestCase();
    }
    
    return 0;
}
