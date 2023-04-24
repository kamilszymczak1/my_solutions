#include <cstdio>
#include <vector>

using namespace std;

using namespace std;

const int MAX_N = 100'000, LOG = 20;

int subtree[MAX_N], dist_to_centroid[LOG][MAX_N];
int super_parent[LOG][MAX_N], centroid_parent[LOG][MAX_N];
long long total_subtree_dist[LOG][MAX_N], total_centroid_dist[LOG][MAX_N];
int centroid_node_count[LOG][MAX_N], sparent_node_count[LOG][MAX_N];
bool erased[MAX_N];

vector<pair<int, int>>adj[MAX_N];
int n, k;

void gather(int x, int parent, vector<int>&nodes) {
    subtree[x] = 1;
    nodes.push_back(x);
    for(auto [y, c] : adj[x]) {
        if(y != parent && !erased[y]) {
            gather(y, x, nodes);
            subtree[x] += subtree[y];
        }
    }
}

void dfs_prep(int x, int parent, int level, long long dist, int sparent, int centroid) {
    dist_to_centroid[level][x] = dist;
    super_parent[level][x] = sparent;
    centroid_parent[level][x] = centroid;
    for(auto [y, c] : adj[x]) {
        if(y != parent && !erased[y]) {
            dfs_prep(y, x, level, dist + c, sparent, centroid);
        }
    }
}

void make_centroid_tree(int x, int level) {
    vector<int>nodes;
    gather(x, -1, nodes);
    int nodes_count = nodes.size();
    int centroid = x;
    for(int y : nodes) {
        if(subtree[y] * 2 >= nodes_count && subtree[y] < subtree[centroid]) {
            centroid = y;
        }
    }
    dist_to_centroid[level][centroid] = 0;
    super_parent[level][centroid] = centroid;
    centroid_parent[level][centroid] = centroid;
    for(auto [y, c] : adj[centroid]) {
        if(!erased[y]) {
            dfs_prep(y, centroid, level, c, y, centroid);
        }
        
    }
    erased[centroid] = true;
    for(auto [y, c] : adj[centroid]) {
        if(!erased[y]) {
            make_centroid_tree(y, level + 1);
        }
    }
}

long long toggle(int level, int x) {
    int centroid = centroid_parent[level][x];
    int sparent = super_parent[level][x];
    long long centroid_dist = dist_to_centroid[level][x];
    
    long long answer = total_centroid_dist[level][centroid];
    if(x != centroid) {
        answer += toggle(level + 1, x);
        answer -= total_subtree_dist[level][sparent];
        answer += (centroid_node_count[level][centroid] - sparent_node_count[level][sparent]) * centroid_dist;
        total_centroid_dist[level][centroid] += centroid_dist;
        total_subtree_dist[level][sparent] += centroid_dist;
    }
    centroid_node_count[level][centroid]++;
    sparent_node_count[level][sparent]++;
    return answer;
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n - 1; i++) { 
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        adj[a - 1].emplace_back(b - 1, c);
        adj[b - 1].emplace_back(a - 1, c);
    }
    make_centroid_tree(0, 0);
    toggle(0, 0);
    long long answer = 0;
    while(k--) {
        int x; scanf("%d", &x);
        answer += toggle(0, x - 1);
        printf("%lld\n", answer * 2);
    }
    return 0;
}
