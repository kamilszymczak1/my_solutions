#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
 
using namespace std;
 
const int MAX_N = 200'007;
 
const long long inf = 1ll << 60;
const int s_inf = 1 << 30;
 
pair<int, int>edges[MAX_N];
vector<pair<int, int>>adj[MAX_N];
set<int>occupied[MAX_N];
vector<pair<int, int>>occupied_int[MAX_N];
long long min_dist[MAX_N];
int n, m, p, l;
 
void dijkstra(int source) {
    for(int i = 0; i < n; i++)
        min_dist[i] = inf;
    min_dist[source] = 0;
    
    set<pair<long long, int>>s;
    
    for(int i = 0; i < n; i++)
        s.insert(make_pair(min_dist[i], i));
    
    while(!s.empty()) {
        auto [my_d, x] = *s.begin();
        s.erase(s.begin());
        
        long long rem = my_d % l;
       
        
        for(auto [y, edge_id] : adj[x]) {
            
            long long wait = 0;
            
            if(occupied[edge_id].size() == l)
                continue;
            
            auto it = occupied[edge_id].lower_bound(rem);
            
            if(it == occupied[edge_id].end() || *it != rem) {
                wait = 0;
            } else {
                int ind = upper_bound(occupied_int[edge_id].begin(), occupied_int[edge_id].end(), make_pair((int)rem, s_inf)) - occupied_int[edge_id].begin() - 1;
                
                if(occupied_int[edge_id][ind].second == l - 1) {
                    int f = occupied_int[edge_id][0].first == 0 ? occupied_int[edge_id][0].second + 1 : 0;
                    wait = l - rem + f;
                } else {
                    wait = occupied_int[edge_id][ind].second + 1 - rem;
                }
            }
            
            
            if(min_dist[y] > min_dist[x] + wait + 1) {
                s.erase(make_pair(min_dist[y], y));
                min_dist[y] = min_dist[x] + wait + 1;
                s.insert(make_pair(min_dist[y], y));
            }
            
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> m >> p >> l;
    
    for(int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
        edges[i].first--;
        edges[i].second--;
        if(edges[i].first > edges[i].second)
            swap(edges[i].first, edges[i].second);
    }
    
    sort(edges, edges + m);
    
    for(int i = 0; i < m; i++) {
        adj[edges[i].first].emplace_back(edges[i].second, i);
        adj[edges[i].second].emplace_back(edges[i].first, i);
    }
    
    for(int i = 0; i < p; i++) {
        vector<int>v(l);
        for(int &x : v) {
            cin >> x; x--;
        }
        for(int j = 0; j < l; j++) {
            int x = v[j];
            int y = v[j == l - 1 ? 0 : j + 1];
            
            if(x > y)
                swap(x, y);
            
            int id = lower_bound(edges, edges + m, make_pair(x, y)) - edges;
            
            occupied[id].insert(j);
        }
    }
    
    for(int i = 0; i < m; i++) {
        vector<int>v;
        if(occupied[i].empty())
            continue;
        
        for(int x : occupied[i])
            v.push_back(x);
        
        for(int j = 0; j < (int)v.size(); j++) {
            int k = j;
            while(k < (int)v.size() - 1 && v[k] + 1 == v[k + 1])
                k++;
            occupied_int[i].emplace_back(v[j], v[k]);
            j = k;
        }
    }
    
    int source, target;
    cin >> source >> target;
    source--; target--;
    
    dijkstra(source);
    
    if(min_dist[target] == inf) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << min_dist[target] << '\n';
    }
    
    return 0;
}
