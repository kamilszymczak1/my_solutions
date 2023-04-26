#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int A = 2;
const static int mod[A] = {1'000'000'007, 1'000'000'009};
const static int b[A] = {5, 7};

const int MAX_N = 200'007;

int b_pow[A][MAX_N], subtree_hash[A][MAX_N];
map<int, int>log_b[A];
int labels[MAX_N], labels_hash[A];


vector<int>adj[MAX_N], good_vertices;

void compute_subtree_hashes(int x, int p) {
    for(int j = 0; j < A; j++)
        subtree_hash[j][x] = 1;
    for(int y : adj[x]) {
        if(y == p)
            continue;
        compute_subtree_hashes(y, x);
        for(int j = 0; j < A; j++) {
            subtree_hash[j][x] = (subtree_hash[j][x] + 1ll * b[j] * subtree_hash[j][y]) % mod[j];
        }
    }
}

void find_good_vertices(int x, int p, vector<int>hash_above) {
    vector<int>children_hash_sum(A, 0);
    for(int y : adj[x]) {
        if(y == p)
            continue;
        for(int j = 0; j < A; j++) {
            children_hash_sum[j] += subtree_hash[j][y];
            if(children_hash_sum[j] >= mod[j])
                children_hash_sum[j] -= mod[j];
        }
    }
    
    vector<int>my_hash(A, 0);
    for(int j = 0; j < A; j++) {
        my_hash[j] = hash_above[j] + subtree_hash[j][x];
        if(my_hash[j] >= mod[j])
            my_hash[j] -= mod[j];
    }
    
    bool good = true;
    int missing_dist = -1;
    for(int j = 0; j < A; j++) {
        int diff = my_hash[j] - labels_hash[j] + mod[j];
        if(diff >= mod[j])
            diff -= mod[j];
        
        if(log_b[j].find(diff) == log_b[j].end() || (missing_dist != -1 && log_b[j][diff] != missing_dist)) {
            good = false;
            break;
        }
        
        missing_dist = log_b[j][diff];
    }
    
    
    
    if(good) {
        good_vertices.push_back(x);
    }
    
    for(int y : adj[x]) {
        if(y == p)
            continue;
        
        vector<int>new_hash_above(A, 0);
        for(int j = 0; j < A; j++) {
            int t = 1ll * b[j] * b[j] % mod[j];
            new_hash_above[j] = (1ll * (children_hash_sum[j] - subtree_hash[j][y] + mod[j]) * t + 1ll * (hash_above[j] + 1) * b[j]) % mod[j];
        }
        find_good_vertices(y, x, new_hash_above);
    }
    
    
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    for(int i = 0; i < A; i++) {
        b_pow[i][0] = 1;
        log_b[i][b_pow[i][0]] = 0;
    }
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < A; j++) {
            b_pow[j][i] = 1ll * b_pow[j][i - 1] * b[j] % mod[j];
            log_b[j][b_pow[j][i]] = i;
        }
    }
    
    for(int i = 0; i < n - 1; i++) {
        int x; cin >> x;
        labels[x]++;
    }
    
    for(int i = n - 1; i >= 0; i--) {
        for(int j = 0; j < A; j++) {
            labels_hash[j] = (1ll * labels_hash[j] * b[j] + labels[i]) % mod[j];
        }
    }
    
    for(int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    
    compute_subtree_hashes(0, -1);
    
    vector<int>hash_above(A, 0);
    find_good_vertices(0, -1, hash_above);
    
    cout << good_vertices.size() << '\n' << flush;
    
    sort(good_vertices.begin(), good_vertices.end());
    
    for(int x : good_vertices)
        cout << x + 1 << ' ';
    cout << '\n';
    
    return 0;
}
