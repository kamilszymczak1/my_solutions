#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int MAX_N = 307;
const long long inf = 1ll << 60;
struct Edge {
    int a, b, c;
    Edge() {}
    Edge(int _a, int _b, int _c) {
        a = _a;
        b = _b;
        c = _c;
    }
} edges[MAX_N * MAX_N];
bool operator< (Edge a, Edge b) {
    return a.c < b.c;
}
long long dist[MAX_N][MAX_N], d[MAX_N];
set<pair<int, int>>adj[MAX_N];
int n, m;

struct cmp {
    inline bool operator() (int x, int y) const {
        if(d[x] == d[y])
            return x < y;
        return d[x] < d[y];
    }
};

void Dijkstra(int x) {
    for(int i = 0; i < n; i++)
        d[i] = inf;
    d[x] = 0;
    set<int, cmp>s;
    for(int i = 0; i < n; i++)
        s.insert(i);
    while(!s.empty()) {
        x = *s.begin();
        s.erase(s.begin());
        for(auto [y, c] : adj[x]) {
            if(d[y] > d[x] + c) {
                s.erase(s.find(y));
                d[y] = d[x] + c;
                s.insert(y);
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            dist[i][j] = inf;
        }
        dist[i][i] = 0;
    }
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d", &edges[i].a, &edges[i].b, &edges[i].c);
        edges[i].a--;
        edges[i].b--;
        adj[edges[i].a].insert(make_pair(edges[i].b, edges[i].c));
        adj[edges[i].b].insert(make_pair(edges[i].a, edges[i].c));
        dist[edges[i].a][edges[i].b] = edges[i].c;
        dist[edges[i].b][edges[i].a] = edges[i].c;
    }
    
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    
    sort(edges, edges + m);
    int result = 0;
    for(int i = m - 1; i >= 0; i--) {
        int a = edges[i].a, b = edges[i].b, c = edges[i].c;
        if(dist[a][b] < c) {
            result++;
        } else {
            for(int j = 0; j < n; j++) {
                if(j == a || j == b)
                    continue;
                if(dist[a][j] + dist[j][b] == c) {
                    result++;
                    break;
                }
            }
        }
    }
    printf("%d\n", result);
    
    return 0;
}
