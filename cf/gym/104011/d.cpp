#include <iostream>
#include <vector>
#include <algorithm>
    
using namespace std;
    
struct seg_tree {
    struct tree_node {
        tree_node *left, *right;
        int max_left, max_right, max_mid, weight;
        tree_node() {
            max_left = max_right = max_mid = weight = 0;
            left = right = NULL;
        }
    };
    int leaf_count;
    tree_node *root;
    seg_tree(int n) {
        for(leaf_count = 1; leaf_count < n; leaf_count *= 2) {}
        root = new tree_node();
    }
    
    void merge(tree_node *v, int l, int r) {
        if(v -> left == NULL && v -> right == NULL) {
            v -> max_left = 0;
            v -> max_right = 0;
            v -> max_mid = 0;
            return;
        }
        
        if(v -> left == NULL) {
            v -> max_left = 0;
            v -> max_right = v -> right -> max_right;
            v -> max_mid = v -> right -> max_mid;
            return;
        }
        
        if(v -> right == NULL) {
            v -> max_left = v -> left -> max_left;
            v -> max_right = 0;
            v -> max_mid = v -> left -> max_mid;
            return;
        }
        
        v -> max_left = v -> left -> max_left;
        if(v -> left -> max_left * 2 == r - l)
            v -> max_left = v -> left -> max_left + v -> right -> max_left;
        
        v -> max_right = v -> right -> max_right;
        if(v -> right -> max_right * 2 == r - l)
            v -> max_right = v -> right -> max_right + v -> left -> max_right;
        
        v -> max_mid = max(v -> left -> max_mid, v -> right -> max_mid);
        v -> max_mid = max(v -> max_mid, v -> left -> max_right + v -> right -> max_left);
    }
    
    void add_rec(int l, int r, int x, int value, tree_node *v) {
        if(l + 1 == r) {
            v -> weight += value;
            if(v -> weight == 0) {
                v -> max_left = 0;
                v -> max_right = 0;
                v -> max_mid = 0;
            } else {
                v -> max_left = 1;
                v -> max_right = 1;
                v -> max_mid = 1;
            }
            return;
        }
        int mid = (l + r) / 2;
        if(x < mid) {
            if(v -> left == NULL)
                v -> left = new tree_node();
            add_rec(l, mid, x, value, v -> left);
        } else {
            if(v -> right == NULL)
                v -> right = new tree_node();
            add_rec(mid, r, x, value, v -> right);
        }
        merge(v, l, r);
    }
    
    void add(int x, int value) {
        add_rec(0, leaf_count, x, value, root);
    }
    
    int get() {
        return root -> max_mid;
    }
};
    
void test_case() {
    int n, m; cin >> n >> m;
    vector<int>a(n);
    for(int &x : a)
        cin >> x;
    
    seg_tree t(a.back() / m + 3);
    
    vector<pair<int, int>>changes;
    
    for(int x : a) {
        t.add(x / m, 1);
        if(x % m != 0) {
            changes.emplace_back(m - x % m, x / m);
        }
    }
    
    int best_time = 0;
    int answer = 0;
    
    sort(changes.begin(), changes.end());
    
    int previous = 0;
    
    for(auto [my_time, ind] : changes) {
        if(my_time != previous) {
            if(t.get() > answer) {
                answer = t.get();
                best_time = previous;
            }
            previous = my_time;
        }
        
        
        t.add(ind + 0, -1);
        t.add(ind + 1, +1);
        
    }
    
    if(t.get() > answer) {
        answer = t.get();
        best_time = previous;
    }
    
    cout << answer << ' ' << best_time << '\n';
}
    
int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        test_case();
    return 0;
}
