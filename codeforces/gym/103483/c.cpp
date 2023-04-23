#include <iostream>
#include <array>
#include <vector>
    
#pragma GCC optimize("Ofast,unroll-loops")
    
using namespace std;
    
const int A = 26;
    
struct trie {
    struct trie_node {
        int sons[A], son_jumps[A];
        int parent, parent_jump, depth, subtree, dp, my_value;
        trie_node(int _parent, int _depth) {
            for(int i = 0; i < A; i++) {
                sons[i] = son_jumps[i] = -1;
            }
            parent = _parent;
            depth = _depth;
            subtree = 0;
            dp = 0;
            my_value = 0;
        }
    };
    vector<trie_node>nodes;
    int my_position, my_len, next_character;
    trie() {
        nodes.resize(1, trie_node(-1, 0));
    }
    
    int new_node(int parent) {
        nodes.emplace_back(parent, nodes[parent].depth + 1);
        return (int)nodes.size() - 1;
    }
    
    void add_string(string &s) {
        int node = 0;
        for(char c : s) {
            nodes[node].subtree++;
            if(nodes[node].sons[c - 'a'] == -1) { 
                int t = new_node(node);
                nodes[node].sons[c - 'a'] = t;
            }
            node = nodes[node].sons[c - 'a'];
        }
        nodes[node].subtree++;
        nodes[node].my_value++;
    }
    
    void calc_son_jumps(int node) {
        for(int i = 0; i < A; i++) {
            if(nodes[node].sons[i] != -1){
                
                int son = nodes[node].sons[i];
                int son_jump = nodes[son].son_jumps[i];
                int son_jump_jump = nodes[son_jump].son_jumps[i];
                
                if(nodes[son_jump].depth - nodes[son].depth == nodes[son_jump_jump].depth - nodes[son_jump].depth) {
                    nodes[node].son_jumps[i] = son_jump_jump;
                } else {
                    nodes[node].son_jumps[i] = son;
                }
                
            } else {
                nodes[node].son_jumps[i] = node;
            }
        }
    }
    
    void calc_jumps_rec(int node) {
        int parent = nodes[node].parent;
        int parent_jump = nodes[parent].parent_jump;
        int parent_jump_jump = nodes[parent_jump].parent_jump;
        if(nodes[parent].depth - nodes[parent_jump].depth == nodes[parent_jump].depth - nodes[parent_jump_jump].depth) {
            nodes[node].parent_jump = parent_jump_jump;
        } else {
            nodes[node].parent_jump = parent;
        }
        
        for(int i = 0; i < A; i++) {
            if(nodes[node].sons[i] != -1) {
                calc_jumps_rec(nodes[node].sons[i]);
            }
        }
        
        calc_son_jumps(node);
    }
    
    void calc_jumps() {
        nodes[0].parent_jump = 0;
        for(int i = 0; i < A; i++) {
            if(nodes[0].sons[i] != -1) {
                calc_jumps_rec(nodes[0].sons[i]);
            }
        }
        calc_son_jumps(0);
    }
    
    void calc_dp_rec(int node) {
        int my_dp = nodes[node].dp + nodes[node].my_value;
        for(int j = 0; j < A; j++) {
            if(nodes[node].sons[j] != -1) {
                nodes[nodes[node].sons[j]].dp = my_dp;
                calc_dp_rec(nodes[node].sons[j]);
                
                my_dp += nodes[nodes[node].sons[j]].subtree;
            }
        }
    }
    
    void calc_dp() {
        calc_dp_rec(0);
    }
    
    int jump_up(int node, int dist) {
        int target_depth = nodes[node].depth - dist;
        while(nodes[node].depth != target_depth) {
            if(nodes[nodes[node].parent_jump].depth >= target_depth) {
                node = nodes[node].parent_jump;
            } else {
                node = nodes[node].parent;
            }
        }
        return node;
    }
    
    int jump_down(int node, char c, int dist) {
        int target_depth = nodes[node].depth + dist;
        while(nodes[node].depth != target_depth && nodes[node].sons[c - 'a'] != -1) {
            if(nodes[nodes[node].son_jumps[c - 'a']].depth <= target_depth) {
                node = nodes[node].son_jumps[c - 'a'];
            } else {
                node = nodes[node].sons[c - 'a'];
            }
        }
        return node;
    }
    
    void init_queries(string &s) {
        my_len = s.size();
        my_position = 0;
        for(char c : s) {
            if(nodes[my_position].sons[c - 'a'] == -1) {
                next_character = c;
                return;
            }
            my_position = nodes[my_position].sons[c - 'a'];
        }
        next_character = -1;
    }
    
    
    int get_answer() {
        int answer = nodes[my_position].dp + (next_character == -1 ? 0 : nodes[my_position].my_value);
        for(int i = 'a'; i < next_character; i++) {
            if(nodes[my_position].sons[i - 'a'] != -1) {
                answer += nodes[nodes[my_position].sons[i - 'a']].subtree;
            }
        }
        return answer;
    }
    
    void update(int k, char c) {
        int current_len = nodes[my_position].depth;
        
        if(k > current_len) {
            return;
        }
        
        my_position = jump_up(my_position, current_len - k);
        
        my_position = jump_down(my_position, c, my_len - nodes[my_position].depth);
        
        if(nodes[my_position].depth == my_len) {
            next_character = -1;
        } else {
            next_character = c;
        }
    }
    
};
    
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n, q; cin >> n >> q;
    
    trie t;
    string s; cin >> s;
    for(int i = 0; i < n; i++) {
        string x; cin >> x;
        t.add_string(x);
    }
    
    t.calc_jumps();
    t.calc_dp();
    
    t.init_queries(s);
    
    cout << t.get_answer() << '\n';
    for(int i = 0; i < q; i++) {
        int k; cin >> k;
        char c; cin >> c;
        t.update(k - 1, c);
        cout << t.get_answer() << '\n';
    }
    
    return 0;
}
