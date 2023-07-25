#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

struct query {
    int l, r, lo, hi, id;
    query() {}
    query(int _l, int _r, int _lo, int _hi, int _id) : l(_l), r(_r), lo(_lo), hi(_hi), id(_id) {}
    int mid() { return (lo + hi) / 2; }
};

bool operator< (query a, query b) {
    return a.mid() < b.mid();
}

struct solver {
    struct Node {
        int x[3], y[3];
        Node() {
            for(int i = 0; i < 3; i++)
                x[i] = y[i] = 0;
        }
        Node(int _x1, int _x2, int _x3, int _y1, int _y2, int _y3) {
            x[0] = _x1; y[0] = _y1;
            x[1] = _x2; y[1] = _y2;
            x[2] = _x3; y[2] = _y3;
        }
    };
    const Node zero_node = Node(0, 0, 0, 1, 2, 1);
    const Node one_node = Node(1, 0, 0, 0, 0, 1);
    vector<Node>nodes;
    int leaf_count;
    
    Node merge(Node left, Node right) {
        Node result;
        for(int my_y = 0; my_y < 3; my_y++) {
            int new_x = left.x[my_y];
            int new_y = left.y[my_y];
            new_x += right.x[new_y];
            new_y = right.y[new_y];
            result.x[my_y] = new_x;
            result.y[my_y] = new_y;
        }
        return result;
    }
    
    solver(int n) {
        for(leaf_count = 1; leaf_count < n; leaf_count *= 2) {}
        nodes.resize(leaf_count * 2, zero_node);
        for(int i = leaf_count - 1; i > 0; i--)
            nodes[i] = merge(nodes[i * 2], nodes[i * 2 + 1]);
    }
    
    void toggle(int x) {
        nodes[x + leaf_count] = one_node;
        for(x = (x + leaf_count) / 2; x > 0; x /= 2)
            nodes[x] = merge(nodes[x * 2], nodes[x * 2 + 1]);
    }
    
    bool query(int l, int r) {
        l += leaf_count;
        r += leaf_count;
        if(l == r)
            return nodes[l].x[0] == 1;
        vector<int>path_l(1, l), path_r(1, r);
        while(l / 2 != r / 2) {
            if(l % 2 == 0)
                path_l.push_back(l + 1);
            if(r % 2 == 1)
                path_r.push_back(r - 1);
            l /= 2;
            r /= 2;
        }
        Node result = nodes[path_l[0]];
        for(int i = 1; i < (int)path_l.size(); i++)
            result = merge(result, nodes[path_l[i]]);
        for(int i = (int)path_r.size() - 1; i >= 0; i--)
            result = merge(result, nodes[path_r[i]]);
        return result.x[0] > result.y[0];
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    
    int n; cin >> n;
    vector<pair<int, int>>v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }
    
    sort(v.begin(), v.end(), greater<pair<int, int>>());
    
    int q; cin >> q;
    vector<query>queries;
    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        queries.emplace_back(l - 1, r - 1, 0, n - 1, i);
    }
    
    
    bool searching;
    do {
        searching = false;
        
        sort(queries.begin(), queries.end());
        
        solver my_solver(n);
        
        int v_ind = 0;
        for(query &q : queries) {
            
            while(v_ind < n && v[v_ind].first >= v[q.mid()].first) {
                my_solver.toggle(v[v_ind].second);
                v_ind++;
            }
            
            if(my_solver.query(q.l, q.r)) {
                q.hi = q.mid();
            } else {
                q.lo = q.mid() + 1;
            }
            
            if(q.lo != q.hi)
                searching = true;
        }
        
    } while(searching);
    
    vector<int>answer(q);
    for(query q : queries)
        answer[q.id] = v[q.lo].first;
    
    for(int x : answer)
        cout << x << '\n';
    
    return 0;
}
