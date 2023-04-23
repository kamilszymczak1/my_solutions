#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const long long mod = 1'000'000'007;

void TestCase() {
    int n, m; scanf("%d%d", &n, &m);
    int s, t; scanf("%d%d", &s, &t);
    s--; t--;
    vector<vector<int>>adj(n);
    for(int i = 0; i < m; i++) {
        int x, y; scanf("%d%d", &x, &y);
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    
    vector<int>dist(n, n + 10);
    vector<int>dp1(n, 0), dp2(n, 0);
    dp1[s] = 1;
    dist[s] = 0;
    vector<int>q; q.push_back(s);
    for(int i = 0; i < (int)q.size(); i++) {
        int x = q[i];
        for(int y : adj[x]) {
            if(dist[y] > dist[x] + 1) {
                dp1[y] = dp1[x];
                dist[y] = dist[x] + 1;
                q.push_back(y);
            } else if(dist[y] == dist[x] + 1) {
                dp1[y] = (dp1[y] + dp1[x]) % mod;
            }
        }
    }
    
    for(int i = 0; i < (int)q.size(); i++) {
        int x = q[i];
        for(int y : adj[x]) {
            if(dist[y] == dist[x] - 1) {
                dp2[x] = (dp2[x] + dp2[y]) % mod;
            } else if(dist[y] == dist[x]) {
                dp2[x] = (dp2[x] + dp1[y]) % mod;
            }
        }
    }
    printf("%lld\n", (dp1[t] + dp2[t]) % mod);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    
    return 0;
}
