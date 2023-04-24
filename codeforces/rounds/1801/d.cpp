#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <algorithm>
#include <bitset>

using namespace std;

const long long inf = 1ll << 60;

long long ceil(long long x, long long y) {
    long long k = x / y;
    if(k * y == x)
        return k;
    return k + 1;
}

void dijkstra(int source, vector<vector<pair<int, long long>>>&adj, vector<long long>&min_dist) {
    int n = adj.size();
    fill(min_dist.begin(), min_dist.end(), inf);
    min_dist[source] = 0;
    set<pair<long long, int>>s;
    for(int i = 0; i < n; i++)
        s.insert(make_pair(min_dist[i], i));
    while(!s.empty()) {
        auto [w, x] = *s.begin();
        s.erase(s.begin());
        for(auto [y, ww] : adj[x]) {
            if(min_dist[y] > w + ww) {
                s.erase(make_pair(min_dist[y], y));
                min_dist[y] = w + ww;
                s.insert(make_pair(min_dist[y], y));
            }
        }
    }
}

void test_case() {
    int n, m, p; cin >> n >> m >> p;
    vector<long long>w(n);
    vector<pair<int, int>>w_ind;
    for(int i = 0; i < n; i++) {
        cin >> w[i];
        w_ind.emplace_back(w[i], i);
    }
    
    vector<vector<pair<int, long long>>>rev_adj(n);
    
    for(int i = 0; i < m; i++) {
        int x, y, w; cin >> x >> y >> w;
        rev_adj[y - 1].emplace_back(x - 1, w);
    }
    
    sort(w_ind.begin(), w_ind.end());
    
    vector<pair<long long, long long>>dp(n, make_pair(inf, 0ll));
    dp[0] = make_pair(0, p);
    
    vector<long long>min_dist(n);
    
    for(auto [ww, i] : w_ind) {
        dijkstra(i, rev_adj, min_dist);
        
        for(int j = 0; j < n; j++) {
            if(i == j || min_dist[j] == inf || dp[j] == make_pair(inf, 0ll))
                continue;
            
            long long profit = w[j];
            long long base_coins = dp[j].second;
            long long travel_cost = min_dist[j];
            
            long long performances = 0;
            if(travel_cost > base_coins) {
                performances = ceil(travel_cost - base_coins, profit);
            }
            
            long long new_base_coins = performances * profit + base_coins - travel_cost;
            
            long long new_performances = performances + dp[j].first;
            
            if(new_performances < dp[i].first) {
                dp[i] = make_pair(new_performances, new_base_coins);
            } else if(new_performances == dp[i].first) {
                dp[i].second = max(dp[i].second, new_base_coins);
            }
        }
    }
    
    long long answer = inf;
    dijkstra(n - 1, rev_adj, min_dist);
    
    for(int i = 0; i < n; i++) {
        if(min_dist[i] == inf || dp[i] == make_pair(inf, 0ll))
            continue;
        long long my_performances = dp[i].first;
        long long my_coins = dp[i].second;
        long long my_travel_cost = min_dist[i];
        
        long long performances = 0;
        if(my_travel_cost > my_coins) {
            performances = ceil(my_travel_cost - my_coins, w[i]);
        }
        
        answer = min(answer, performances + my_performances);
    }
    
    if(answer == inf) {
        cout << "-1\n";
    } else {
        cout << answer << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        test_case();
    
    return 0;
}
