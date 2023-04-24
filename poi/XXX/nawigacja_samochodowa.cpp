#include <iostream>
#include <cassert>
#include <vector>
#include <bitset>

using namespace std;

const int B = 512;
const int MAX_N = 200'007;
const int T = 18;

bitset<B>codes[MAX_N];
bool erased[MAX_N];
int subtree[MAX_N], subtree_id[MAX_N], subtree_dist[MAX_N];
vector<int>adj[MAX_N];

void gather(int x, int p, vector<int>&nodes) {
    nodes.push_back(x);
    subtree[x] = 1;
    for(int y : adj[x]) {
        if(!erased[y] && y != p) {
            gather(y, x, nodes);
            subtree[x] += subtree[y];
        }
    }
}

void dfs(int x, int p, int current_subtree_id) {
    subtree_id[x] = current_subtree_id;
    for(int y : adj[x]) {
        if(!erased[y] && y != p) {
            subtree_dist[y] = subtree_dist[x] + 1;
            dfs(y, x, current_subtree_id);
        }
    }
}

void run_centroids(int x, int bit_prefix, int bit_len) {
    assert(bit_len > 0);
    vector<int>nodes;
    gather(x, -1, nodes);
    
    int centroid = x, n = nodes.size();
    for(int y : nodes) {
        if(subtree[y] * 2 >= n && subtree[y] < subtree[centroid]) {
            centroid = y;
        }
    }
    
    subtree_id[centroid] = subtree_dist[centroid] = 0;
    int current_subtree_id = 0;
    for(int y : adj[centroid]) {
        if(erased[y])
            continue;
        subtree_dist[y] = 1;
        dfs(y, centroid, ++current_subtree_id);
    }
    
    for(int y : nodes) {
        bitset<B>my_dist(subtree_dist[y]);
        bitset<B>my_id(subtree_id[y]);
        
        my_id <<= bit_prefix;
        my_dist <<= (bit_prefix + bit_len);
        
        codes[y] |= my_id | my_dist;
    }
    
    erased[centroid] = true;
    for(int y : adj[centroid]) {
        if(!erased[y]) {
            run_centroids(y, bit_prefix + bit_len * 2, bit_len - 1);
        }
    }
}

void enkoder() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n;
    for(int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    
    run_centroids(0, 0, T);
    
    for(int i = 0; i < n; i++) {
        cout << codes[i].to_string() << '\n';
    }
}

int decode(int bit_prefix, int bit_len, bitset<B>&x, bitset<B>&y) {
    bitset<B>all_ones((1ll << bit_len) - 1);
    int x_id = ((x >> bit_prefix) & all_ones).to_ullong();
    int y_id = ((y >> bit_prefix) & all_ones).to_ullong();
    int x_dist = ((x >> (bit_prefix + bit_len)) & all_ones).to_ullong();
    int y_dist = ((y >> (bit_prefix + bit_len)) & all_ones).to_ullong();
    
    if(x_id == 0 || y_id == 0 || x_id != y_id)
        return x_dist + y_dist;
    return decode(bit_prefix + 2 * bit_len, bit_len - 1, x, y);
}

void dekoder() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int m; cin >> m;
    while(m--) {
        string p, q; cin >> p >> q;
        bitset<B>x(p), y(q);
        cout << decode(0, T, x, y) << '\n';
    }
}
