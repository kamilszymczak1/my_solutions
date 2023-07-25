#include <iostream>
#include <iomanip>
    
using namespace std;
    
const int MAX_N = 1007;
    
const long long inf = 1ll << 60;
    
string s;
int n;
    
long long dp_min[MAX_N][MAX_N], dp_max[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
    
pair<long long, long long>get(int l, int r) {
    if(l > r)
        return make_pair(inf, -inf);
    if(visited[l][r])
        return make_pair(dp_min[l][r], dp_max[l][r]);
    
    visited[l][r] = true;
    dp_min[l][r] = +inf;
    dp_max[l][r] = -inf;
    
    if(s[l] == '0') {
        if(l == r)
            dp_min[l][r] = dp_max[l][r] = 0;
    } else if(s[l] == '+') {
        for(int i = l + 1; i < r; i++) {
            auto [a1, b1] = get(l + 1, i + 0);
            auto [a2, b2] = get(i + 1, r);
            if(a1 != inf && a2 != inf) {
                dp_min[l][r] = min(dp_min[l][r], a1 + a2);
                dp_max[l][r] = max(dp_max[l][r], b1 + b2);
            }
        }
    } else if(s[l] == '-') {
        for(int i = l + 1; i < r; i++) {
            auto [a1, b1] = get(l + 1, i + 0);
            auto [a2, b2] = get(i + 1, r);
            if(a1 != inf && a2 != inf) {
                dp_min[l][r] = min(dp_min[l][r], a1 - b2);
                dp_max[l][r] = max(dp_max[l][r], b1 - a2);
            }
        }
        
        auto [x, y] = get(l + 1, r);
        if(x != inf) {
            dp_min[l][r] = min(dp_min[l][r], -y);
            dp_max[l][r] = max(dp_max[l][r], -x);
        }
    } else {
        if(r - l + 1 <= 9) {
            long long value = 0;
            for(int i = l; i <= r; i++) {
                if(s[i] < '0' || s[i] > '9')
                    return make_pair(dp_min[l][r], dp_max[l][r]);
                value = value * 10 + s[i] - '0';
            }
            dp_min[l][r] = dp_max[l][r] = value;
        }
    }
    
    return make_pair(dp_min[l][r], dp_max[l][r]);
}
    
int main() {
    ios_base::sync_with_stdio(0);
    while(cin >> s) {
        n = s.size();
        for(int i = 0; i < n; i++) {
            for(int j = i; j < n; j++) {
                visited[i][j] = false;
            }
        }
        auto [x, y] = get(0, n - 1);
        cout << x << ' ' << y << '\n';       
    }
    return 0;
}
