#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <cassert>
#include <cmath>
#include <set>

using namespace std;

const int MAX_N = 100'001;

const long long inf = 1ll << 60;

struct LiChao {
    //what a fancy data structure
    
    struct Node {
        long long a, b;
        Node() : a(0), b(inf) {}
    };
    
    vector<Node>nodes;
    int leaf_count;
    
    LiChao(int n) {
        for(leaf_count = 1; leaf_count < n; leaf_count *= 2) {}
        nodes.resize(leaf_count * 2);
    }
    
    void insert(long long a, long long b) {
        insert_rec(0, leaf_count, 1, a, b);
    }
    
    void insert_rec(int lo, int hi, int v, long long a, long long b) {
        int mid = (lo + hi) / 2;
        
        long long m1 = nodes[v].a * mid + nodes[v].b;
        long long m2 = a * mid + b;
        
        if(m2 < m1) {
            swap(nodes[v].a, a);
            swap(nodes[v].b, b);
        }
        
        if(hi - lo == 1)
            return;
        
        long long l1 = nodes[v].a * lo + nodes[v].b;
        long long l2 = a * lo + b;
        
        if(l2 < l1)
            insert_rec(lo, mid, v * 2, a, b);
        
        long long r1 = nodes[v].a * hi + nodes[v].b;
        long long r2 = a * hi + b;
        
        if(r2 < r1)
            insert_rec(mid, hi, v * 2 + 1, a, b);
    }
    
    long long get_min(int x) {
        long long result = inf;
        for(int i = x + leaf_count; i > 0; i /= 2)
            result = min(result, nodes[i].a * x + nodes[i].b);
        return result;
    }
    
    void clear() {
        for(int i = 0; i < leaf_count * 2; i++) {
            nodes[i].a = 0;
            nodes[i].b = inf;
        }
    }
};

long long d[MAX_N];
vector<pair<int, int>>adj[MAX_N];
int n, m, k;

struct cmp {
    inline bool operator() (const int a, const int b) const {
        if(d[a] == d[b])
            return a < b;
        return d[a] < d[b];
    }
};

void dijkstra() {
    
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>>q;
    for(int i = 0; i < n; i++)
        q.push(make_pair(d[i], i));
    
    while(!q.empty()) {
        auto [D, x] = q.top();
        q.pop();
        if(d[x] != D)
            continue;
        for(auto [y, w] : adj[x]) {
            if(d[y] > d[x] + w) {
                d[y] = d[x] + w;
                q.push(make_pair(d[y], y));
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 0; i < m; i++) {
        int x, y; scanf("%d%d", &x, &y);
        int w; scanf("%d", &w);
        adj[x - 1].emplace_back(y - 1, w);
        adj[y - 1].emplace_back(x - 1, w);
    }
    
    for(int i = 0; i < n; i++)
        d[i] = inf;
    d[0] = 0;
    
    LiChao T(n);
    while(k--) {
        dijkstra();
        
        for(int k = 0; k < 2; k++) {
            
            for(int i = 0; i < n; i++) {
                long long my_value = T.get_min(i) + 1ll * i * i;
                
                T.insert(-2 * i, d[i] + 1ll * i * i);
                d[i] = min(d[i], my_value);
            }
            T.clear();
            reverse(d, d + n);
        }
    }
    dijkstra();
    for(int i = 0; i < n; i++)
        printf("%lld ", d[i]);
    printf("\n");
    
    return 0;
}
