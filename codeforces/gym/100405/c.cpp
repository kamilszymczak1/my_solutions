#include <iostream>
#include <vector>
#include <iomanip>
    
using namespace std;
    
int value(string s) {
    if(s.size() == 2)
        return 10;
    if('0' <= s[0] && s[0] <= '9')
        return s[0] - '0';
    if(s == "A")
        return 11;
    return 10;
}
    
const int MAX_N = 10'000;
int card_type[MAX_N];
long double dp[MAX_N];
    
long double prob(int x, int y) {
    if(y - x > 11)
        return 0;
    if(card_type[x] != 0) {
        if(x + card_type[x] == y)
            return 1;
        return 0;
    }
    int dist = y - x;
    if(dist < 2)
        return 0;
    if(dist == 10)
        return 4.0 / 13;
    return 1.0 / 13;
}
    
int main() {
    ios_base::sync_with_stdio(0);
    
    int n, m;
    while(cin >> n >> m) {
        vector<int>values;
        int cards = m;
        for(int i = 0; i < n; i++){
            string s; cin >> s;
            values.push_back(value(s));
            cards += values.back();
        }
        cards -= values.back();
        fill(card_type, card_type + cards, 0);
        int pos = m - 1;
        for(int x : values) {
            card_type[pos] = x;
            pos += x;
        }
        
        for(int i = 0; i < cards; i++) {
            dp[i] = i < 10 ? 0.1 : 0;
            for(int j = max(0, i - 11); j < i; j++) {
                dp[i] += dp[j] * prob(j, i);
            }
        }
        
        cout << fixed << setprecision(20) << dp[cards - 1] << '\n';
        
    }
    
    
    return 0;
}
