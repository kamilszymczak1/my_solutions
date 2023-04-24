#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int MAX_N = 500'007;

struct seg_tree {
    vector<long long>v;
    int leaf_count;
    seg_tree() {}
    seg_tree(int n) {
        for(leaf_count = 1; leaf_count < n; leaf_count *= 2) {}
        v.resize(leaf_count * 2, 0);
    }
    
    long long prefix_sum(int x) {
        long long result = v[x + leaf_count];
        for(x += leaf_count; x > 1; x /= 2) {
            if(x % 2 == 1) {
                result += v[x - 1];
            }
        }
        return result;
    }
    
    long long suffix_sum(int x) {
        long long result = v[x + leaf_count];
        for(x += leaf_count; x > 1; x /= 2) {
            if(x % 2 == 0) {
                result += v[x + 1];
            }
        }
        return result;
    }
    
    void add(int x, long long value) {
        for(x += leaf_count; x > 0; x /= 2)
            v[x] += value;
    }
};

vector<int>adj[MAX_N];
bool in_A[MAX_N], in_B[MAX_N];
int in_both_sets = 0, dist[MAX_N];
int n, q, sa, sb;
seg_tree tree_a, tree_b;

seg_tree tree_A[2], tree_B[2];

long long total = 0;

int subtree[MAX_N], id[MAX_N];

void dfs_dist(int x, int p, int my_id) {
    id[x] = my_id;
    for(int y : adj[x]) {
        if(y == p)
            continue;
        dist[y] = dist[x] + 1;
        dfs_dist(y, x, my_id);
    }
}

void centro_dfs(int x, int p, vector<int>&centroids) {
    subtree[x] = 1;
    bool centro = true;
    for(int y : adj[x]) {
        if(y == p)
            continue;
        centro_dfs(y, x, centroids);
        subtree[x] += subtree[y];
        if(subtree[y] * 2 > n)
            centro = false;
    }
    if((n - subtree[x]) * 2 > n)
        centro = false;
    if(centro)
        centroids.push_back(x);
}

void add_to_A(int w) {
    if(in_B[w]) {
        in_both_sets++;
    }
    total += tree_b.suffix_sum(dist[w]);
    tree_a.add(dist[w], 1);
    in_A[w] = true;
}

void add_to_B(int w) {
    if(in_A[w]) {
        in_both_sets++;
    }
    total += tree_a.prefix_sum(dist[w]);
    tree_b.add(dist[w], 1);
    in_B[w] = true;
}

void remove_from_A(int w) {
    if(in_B[w]) {
        in_both_sets--;
    }
    total -= tree_b.suffix_sum(dist[w]);
    tree_a.add(dist[w], -1);
    in_A[w] = false;
}

void remove_from_B(int w) {
    if(in_A[w]) {
        in_both_sets--;
    }
    total -= tree_a.prefix_sum(dist[w]);
    tree_b.add(dist[w], -1);
    in_B[w] = false;
}

void add_to_A_2(int w) {
    if(in_B[w]) {
        in_both_sets++;
    }
    int my_id = id[w];
    total += tree_B[my_id].suffix_sum(dist[w]);
    total += tree_B[my_id ^ 1].suffix_sum(dist[w] + 1);
    tree_A[my_id].add(dist[w], 1);
    in_A[w] = true;
}

void add_to_B_2(int w) {
    if(in_A[w]) {
        in_both_sets++;
    }
    int my_id = id[w];
    total += tree_A[my_id].prefix_sum(dist[w]);
    if(dist[w] > 0)
        total += tree_A[my_id ^ 1].prefix_sum(dist[w] - 1);
    tree_B[my_id].add(dist[w], 1);
    in_B[w] = true;
}

void remove_from_A_2(int w) {
    if(in_B[w]) {
        in_both_sets--;
    }
    int my_id = id[w];
    total -= tree_B[my_id].suffix_sum(dist[w]);
    total -= tree_B[my_id ^ 1].suffix_sum(dist[w] + 1);
    tree_A[my_id].add(dist[w], -1);
    in_A[w] = false;
}

void remove_from_B_2(int w) {
    if(in_A[w]) {
        in_both_sets--;
    }
    int my_id = id[w];
    total -= tree_A[my_id].prefix_sum(dist[w]);
    if(dist[w] > 0)
        total -= tree_A[my_id ^ 1].prefix_sum(dist[w] - 1);
    tree_B[my_id].add(dist[w], -1);
    in_B[w] = false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for(int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    
    cin >> sa >> sb >> q;
    
    vector<int>centroids;
    centro_dfs(0, -1, centroids);
    
    if(centroids.size() == 1) {
        
        tree_a = seg_tree(n + 7);
        tree_b = seg_tree(n + 7);
        
        int centro = centroids[0];
        
        dist[centroids[0]] = 0;
        dfs_dist(centroids[0], -1, 0);
        
        for(int i = 0; i < sa; i++) {
            int x; cin >> x;
            add_to_A(x - 1);
        }
        for(int i = 0; i < sb; i++) {
            int x; cin >> x;
            add_to_B(x - 1);
        }
        
        cout << total - in_both_sets << '\n';
        
        while(q--) {
            char z, t; cin >> z >> t;
            int w; cin >> w; w--;
            if(z == 'A') {
                if(t == '+') {
                    add_to_A(w);
                } else {
                    remove_from_A(w);
                }
            } else {
                if(t == '+') {
                    add_to_B(w);
                } else {
                    remove_from_B(w);
                }
            }
            cout << total - in_both_sets << '\n';
        }
        
    } else {
        
        tree_A[0] = seg_tree(n + 7);
        tree_B[0] = seg_tree(n + 7);
        tree_A[1] = seg_tree(n + 7);
        tree_B[1] = seg_tree(n + 7);
        
        int centro1 = centroids[0];
        int centro2 = centroids[1];
        
        dist[centro1] = dist[centro2] = 0;
        dfs_dist(centro1, centro2, 0);
        dfs_dist(centro2, centro1, 1);
        
        for(int i = 0; i < sa; i++) {
            int x; cin >> x;
            add_to_A_2(x - 1);
        }
        for(int i = 0; i < sb; i++) {
            int x; cin >> x;
            add_to_B_2(x - 1);
        }
        
        cout << total - in_both_sets << '\n';
        
        while(q--) {
            char z, t; cin >> z >> t;
            int w; cin >> w; w--;
            if(z == 'A') {
                if(t == '+') {
                    add_to_A_2(w);
                } else {
                    remove_from_A_2(w);
                }
            } else {
                if(t == '+') {
                    add_to_B_2(w);
                } else {
                    remove_from_B_2(w);
                }
            }
            cout << total - in_both_sets << '\n';
        }
            
        
    }
    
    return 0;
}
