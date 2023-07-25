#include <iostream>
#include <vector>
    
using namespace std;
    
const int MAX_N = 200'007, MAX_RAW = 10;
int n, m;
vector<int>ingredients[MAX_N];
int raw_id[MAX_N], raw_count = 0;
vector<int>raws;
long long given_amount[MAX_RAW];
long long raw_required[MAX_N][MAX_RAW];
bool achievable[MAX_N];
long long needed[MAX_RAW];
    
const long long inf = 1ll << 60;
    
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int c; cin >> c;
        if(c == 0) {
            raws.push_back(i);
            raw_id[i] = raw_count++;
            raw_required[i][raw_id[i]] = 1;
            cin >> given_amount[raw_id[i]];
            achievable[i] = true;
        } else {
            for(int j = 0; j < c; j++) {
                int x; cin >> x;
                ingredients[i].push_back(x - 1);
            }
        }
    }
    
    for(int i = m - 1; i >= 0; i--) {
        achievable[i] = true;
        for(int j : ingredients[i]) {
            if(!achievable[j]) {
                achievable[i] = false;
            }
        }
        
        if(!achievable[i])
            continue;
        
        for(int j : ingredients[i]) {
            for(int k = 0; k < raw_count; k++) {
                raw_required[i][k] += raw_required[j][k];
                raw_required[i][k] = min(inf, raw_required[i][k]);
            }
        }
    }
    
    int answer = 0;
    for(int mask = 1; mask < (1 << n); mask++) {
        fill(needed, needed + raw_count, 0);
        bool ok = true;
        for(int j = 0; j < n; j++) {
            if((mask >> j) & 1) {
                if(!achievable[j]) {
                    ok = false;
                }
                for(int k = 0; k < raw_count; k++) {
                    needed[k] += raw_required[j][k];
                    needed[k] = min(needed[k], inf);
                }
            }
        }
        
        for(int j = 0; j < raw_count; j++) {
            if(needed[j] > given_amount[j]) {
                ok = false;
            }
        }
        
        if(ok) {
            answer = max(answer, __builtin_popcount(mask));
        }
    }
    
    cout << answer << '\n';
    
    return 0;
}
