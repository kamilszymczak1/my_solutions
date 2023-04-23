#include <cstdio>
#include <vector>
#include <stack>
#include <set>

using namespace std;

int main() {
    int n; scanf("%d", &n);
    vector<int>h(n);
    for(auto &x : h)
        scanf("%d", &x);
    stack<pair<int, int>>s;
    s.push(make_pair(n + 1, -1));
    vector<vector<int>>next(n);
    vector<int>point(n);
    
    for(int i = 0; i < n; i++) {
        while(s.top().first < h[i])
            s.pop();
        point[i] = s.top().second;
        if(s.top().second != -1) {
            next[s.top().second].push_back(i);
        }
        s.push(make_pair(h[i], i));
    }
    
    vector<int>dp(n);
    for(int i = n - 1; i >= 0; i--) {
        if(next[i].size() == 1) {
            dp[i] = 1;
        } else {
            int sum = 0, hi = 0;
            for(int y : next[i]) {
                sum += dp[y];
                hi = max(hi, dp[y]);
            }
            dp[i] = max(0, 2 * hi - sum);
        }
    }
    
    set<pair<int, int>, greater<pair<int, int>> >bag;
    
    for(int i = 0; i < n; i++) {
        if(point[i] == -1) {
            bag.insert(make_pair(dp[i], i));
        }
    }
    
    vector<pair<int, int>>moves;
    while(!bag.empty()) {
        auto [xH, x] = *bag.begin();
        bag.erase(bag.begin());
        if(bag.empty()) {
            moves.emplace_back(h[x], h[x]);
            for(int t : next[x])
                bag.insert(make_pair(dp[t], t));
        } else {
            auto [yH, y] = *bag.begin();
            bag.erase(bag.begin());
            moves.emplace_back(h[x], h[y]);
            for(int t : next[x])
                bag.insert(make_pair(dp[t], t));
            for(int t : next[y])
                bag.insert(make_pair(dp[t], t));
        }
    }
    
    printf("%d\n", (int)moves.size());
    for(auto [x, y] : moves)
        printf("%d %d\n", x, y);
    
    return 0;
}
