#include <iostream>
#include <vector>
#include <set>
    
using namespace std;
    
const long long inf = 1ll << 60;
    
const long long mod = 1'000'000'007;
    
vector<pair<long long, long long>>dijkstra(int n, vector<vector<pair<int, long long>>>&edges, int source) {
    set<pair<long long, int>>bag;
    vector<long long>min_dist(n, inf), ways(n, 1);
    min_dist[source] = 0;
    for(int i = 0; i < n; i++)
        bag.insert(make_pair(min_dist[i], i));
    
    while(!bag.empty()) {
        auto [d, x] = *bag.begin();
        bag.erase(bag.begin());
        
        for(auto [y, w] : edges[x]) {
            if(min_dist[y] > min_dist[x] + w) {
                bag.erase(bag.find(make_pair(min_dist[y], y)));
                min_dist[y] = min_dist[x] + w;
                ways[y] = ways[x];
                bag.insert(make_pair(min_dist[y], y));
            } else if(min_dist[y] == min_dist[x] + w) {
                ways[y] += ways[x];
                if(ways[y] >= mod)
                    ways[y] -= mod;
            }
        }
    }
    vector<pair<long long, long long>>ans(n);
    for(int i = 0; i < n; i++)
        ans[i] = make_pair(min_dist[i], ways[i]);
    return ans;
}
    
int main() {
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector<vector<pair<int, long long>>>edges(n);
    
    int s, t; cin >> s >> t; s--; t--;
    long long l; cin >> l;
    
    for(int i = 0; i < m; i++) {
        int x, y;
        long long w;
        cin >> x >> y >> w;
        edges[x - 1].emplace_back(y - 1, w);
        edges[y - 1].emplace_back(x - 1, w);
    }
    
    vector<pair<long long, long long>>dist_to_s = dijkstra(n, edges, s);
    vector<pair<long long, long long>>dist_to_t = dijkstra(n, edges, t);
    
    if(dist_to_s[t].first == l) {
        cout << dist_to_s[t].second << '\n';
        return 0;
    }
    
    if(dist_to_s[t].first > l) {
        cout << "0\n";
        return 0;
    }
    
    long long shortest_path = dist_to_s[t].first;
    long long answer = 0;
    for(int x = 0; x < n; x++) {
        if(x == t)
            continue;
        if(dist_to_t[x].first + dist_to_s[x].first == shortest_path) {
            for(auto [y, w] : edges[x]) {
                if(dist_to_t[y].first + dist_to_s[x].first + w == l) {
                    answer += dist_to_t[y].second * dist_to_s[x].second;
                    answer %= mod;
                }
            }
        }
    }
    
    cout << answer << '\n';
    
    return 0;
}
