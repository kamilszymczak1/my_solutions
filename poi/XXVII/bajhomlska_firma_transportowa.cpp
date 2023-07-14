#include <cstdio>
#include <vector>
#include <algorithm>

#define LSB(x) (x & (-x))

using namespace std;

const int MAX_N = 100'007;

int tree[2][MAX_N];

void TreeAdd(int x, int t, int value) {
    x = MAX_N - x - 1;
    for(; x < MAX_N; x += LSB(x))
        tree[t][x] += value;
}

int TreeSuffix(int x, int t) {
    x = MAX_N - x - 1;
    int result = 0;
    for(; x > 0; x -= LSB(x))
        result += tree[t][x];
    return result;
}

struct Edge {
    int to, w, nice;
    Edge(int _to, int _w, int _nice) : to(_to), w(_w), nice(_nice) {}
};

int n, q, subtree[MAX_N];
long long answer[MAX_N];
vector<Edge>adj[MAX_N];
bool erased[MAX_N];

void Gather(int x, int p, vector<int>&nodes) {
    subtree[x] = 1;
    nodes.push_back(x);
    for(Edge e : adj[x]) {
        if(e.to != p && !erased[e.to]) {
            Gather(e.to, x, nodes);
            subtree[x] += subtree[e.to];
        }
    }
}

void GetResult(int x, int p, int w, int nice, int o) {
    answer[w] += TreeSuffix(w + o, 1) + o * nice;
    if(nice)
        answer[w] += TreeSuffix(w + o, 0);
    for(Edge e : adj[x]) {
        if(!erased[e.to] && e.to != p) {
            GetResult(e.to, x, min(w, e.w), max(nice, e.nice), o);
        }
    }
}

void Add(int x, int p, int w, int nice, int value) {
    TreeAdd(w, nice, value);
    for(Edge e : adj[x]) {
        if(!erased[e.to] && e.to != p) {
            Add(e.to, x, min(w, e.w), max(nice, e.nice), value);
        }
    }
}

void RunCentroids(int x) {
    vector<int>nodes;
    Gather(x, -1, nodes);
    int centroid = x, m = nodes.size();
    for(int y : nodes) {
        if(subtree[y] * 2 >= m && subtree[y] < subtree[centroid]) {
            centroid = y;
        }
    }
    
    for(int k = 0; k < 2; k++) {
        for(Edge e : adj[centroid]) {
            if(erased[e.to])
                continue;
            GetResult(e.to, centroid, e.w, e.nice, k);
            Add(e.to, centroid, e.w, e.nice, 1);
        }
        for(Edge e : adj[centroid]) {
            if(erased[e.to])
                continue;
            Add(e.to, centroid, e.w, e.nice, -1);
        }
        reverse(adj[centroid].begin(), adj[centroid].end());
    }
    
    erased[centroid] = true;
    for(Edge e : adj[centroid]) {
        if(!erased[e.to]) {
            RunCentroids(e.to);
        }
    }
}


int main() {
    scanf("%d%d", &n, &q);
    vector<int>scaled;
    for(int i = 1; i < n; i++) {
        int x, y, w, b; scanf("%d%d%d%d", &x, &y, &w, &b);
        adj[x - 1].emplace_back(y - 1, w, b);
        adj[y - 1].emplace_back(x - 1, w, b);
        scaled.emplace_back(w);
    }
    sort(scaled.begin(), scaled.end());
    scaled.resize(unique(scaled.begin(), scaled.end()) - scaled.begin());
    for(int i = 0; i < n; i++) {
        for(Edge &e : adj[i]) {
            e.w = lower_bound(scaled.begin(), scaled.end(), e.w) - scaled.begin();
        }
    }
    
    RunCentroids(0);
    
    for(int i = n; i >= 0; i--)
        answer[i] += answer[i + 1];
    
    for(int i = 0; i < q; i++) {
        int w; scanf("%d", &w);
        int index = lower_bound(scaled.begin(), scaled.end(), w) - scaled.begin();
        printf("%lld\n", answer[index]);
    }
    
    return 0;
}
