#include <cstdio>
#include <vector>
#include <set>
    
using namespace std;
    
const long long inf = 1ll << 60;
    
long long test_case() {
    int n, m; scanf("%d%d", &n, &m);
    vector<int>x(n), y(n), c(n);
    for(int &a : x)
        scanf("%d", &a);
    for(int &a : y)
        scanf("%d", &a);
    for(int &a : c)
        scanf("%d", &a);
    
    vector<vector<pair<int, int>>>adj(m);
    for(int i = 0; i < n; i++) {
        adj[y[i] - 1].emplace_back(x[i] - 1, c[i]);
    }
    
    vector<long long>dist(m, inf);
    set<pair<long long, int>>s;
    vector<int>w(m);
    for(int i = 0; i < m; i++) {
        scanf("%d", &w[i]);
        if(w[i] == 0)
            dist[i] = 0;
        s.insert(make_pair(dist[i], i));
    }
    
    while(!s.empty()) {
        auto [d, x] = *s.begin();
        s.erase(s.begin());
        for(auto [y, l] : adj[x]) {
            if(dist[y] > dist[x] + l) {
                s.erase(s.find(make_pair(dist[y], y)));
                dist[y] = dist[x] + l;
                s.insert(make_pair(dist[y], y));
            }
        }
    }
    
    long long answer = 0;
    for(int i = 0; i < m; i++) {
        if(w[i] == 2) {
            if(dist[i] == inf) {
                return -1;
            } else {
                answer += dist[i];
            }
        }
    }
    return answer;
}
    
int main() {
    int t; scanf("%d", &t);
    for(int i = 1; i <= t; i++) {
        printf("Case #%d: %lld\n", i, test_case());
    }
    return 0;
}
