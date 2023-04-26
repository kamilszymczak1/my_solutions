#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <queue>

using namespace std;

const int inf = 1ll << 30;

int max_dist(int source, vector<vector<pair<int, int>>>&adj, int t) {
    int n = adj.size();
    vector<int>min_dist(n, inf);
    min_dist[source] = 0;
    queue<int>q;
    q.push(source);
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        for(auto [y, tt] : adj[x]) {
            if(tt > t || min_dist[y] <= min_dist[x] + 1)
                continue;
            min_dist[y] = min_dist[x] + 1;
            q.push(y);
        }
    }
    int answer = 0;
    for(int i = 0; i < n; i++)
        answer = max(answer, min_dist[i]);
    return answer;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, m, q; cin >> n >> m >> q;
    
    vector<vector<pair<int, int>>>adj(n);
    
    for(int i = 1; i <= m; i++) {
        int x, y; cin >> x >> y;
        adj[x - 1].emplace_back(y - 1, 0);
        adj[y - 1].emplace_back(x - 1, 0);
    }
    
    for(int i = 1; i <= q; i++) {
        int x, y; cin >> x >> y;
        adj[x - 1].emplace_back(y - 1, i);
        adj[y - 1].emplace_back(x - 1, i);
    }
    
    vector<int>answer(q + 1);
    
    int i = q;
    while(i >= 0) {
        int i_max_dist = max_dist(0, adj, i);
        int lo = 0, hi = i;
        while(lo < hi) {
            int mid = (lo + hi) / 2;
            int mid_max_dist = max_dist(0, adj, mid);
            if(mid_max_dist <= 2 * i_max_dist) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        for(int j = hi; j <= i; j++)
            answer[j] = i_max_dist * 2;
        
        i = hi - 1;
    }
    
    for(int x : answer)
        cout << x << ' ';
    cout << '\n';
    
    return 0;
}
