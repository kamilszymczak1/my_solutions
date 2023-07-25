#include <iostream>
#include <bitset>
#include <vector>
#include <algorithm>
    
using namespace std;
    
const int A = 26;
    
const int mod = 1000000009;
const int B = 7;
    
bool go(vector<pair<string, bitset<A>>> &s) {
    if(s.size() <= 1)
        return true;
    bitset<A>all_and = s[0].second;
    int n = s.size();
    for(int i = 1; i < n; i++)
        all_and &= s[i].second;
    
    if(all_and.to_ulong() == 0)
        return false;
    
    int bit = 0;
    while(all_and[bit] == 0)
        bit++;
    
    for(auto &[ss, b] : s)
        b[bit] = false;

    vector<pair<int, int>>hashes;
    
    for(int i = 0; i < n; i++) {
        int h = 0;
        for(char c : s[i].first) {
            int x = (int)((c - 'a') == bit) + 1;
            h = (1ll * h * B + x) % mod;
        }
        hashes.emplace_back(h, i);
    }
    sort(hashes.begin(), hashes.end());
    
    for(int i = 0; i < n; i++) {
        int j = i;
        vector<pair<string, bitset<A>>>new_s;
        while(j < n && hashes[i].first == hashes[j].first) {
            new_s.push_back(s[hashes[j].second]);
            j++;
        }
        if(!go(new_s))
            return false;
        i = j - 1;
    }
    return true;
}
    
int main() {
    ios_base::sync_with_stdio(0);
    
    int l, n; cin >> l >> n;
    
    vector<pair<string, bitset<A>>>s(n);
    for(int i = 0; i < n; i++) {
        cin >> s[i].first;
        for(char c : s[i].first)
            s[i].second[c - 'a'] = true;
    }
    
    cout << (go(s) ? "YES" : "NO") << '\n';
    
    return 0;
}
