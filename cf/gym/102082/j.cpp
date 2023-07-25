#include <iostream>
#include <vector>
#include <set>
    
using namespace std;
    
void DFS(int x, int p, vector<vector<int>>&adj, vector<vector<int>>&jump, vector<int>&pre, vector<int>&depth, int &t) {
    pre[x] = t++;
    if(p != -1) {
        jump[x].push_back(p);
        for(int i = 0; i < (int)jump[x].size(); i++) {
            if(i < (int)jump[jump[x][i]].size()) {
                jump[x].push_back(jump[jump[x][i]][i]);
            }
        }
    }
    for(int y : adj[x]) {
        if(y != p) {
            depth[y] = depth[x] + 1;
            DFS(y, x, adj, jump, pre, depth, t);
        }
    }
}
    
int lca(int x, int y, vector<vector<int>>&jump, vector<int>&depth) {
    if(depth[x] < depth[y])
        swap(x, y);
    for(int i = (int)jump[x].size() - 1; i >= 0; i--) {
        if(i < (int)jump[x].size() && depth[jump[x][i]] >= depth[y]) {
            x = jump[x][i];
        }
    }
    if(x == y)
        return x;
    for(int i = (int)jump[x].size() - 1; i >= 0; i--) {
        if(i < (int)jump[x].size() && jump[x][i] != jump[y][i]) {
            x = jump[x][i];
            y = jump[y][i];
        }
    }
    return jump[x][0];
}
    
int dist(int x, int y, vector<vector<int>>&jump, vector<int>&depth) {
    return depth[x] + depth[y] - 2 * depth[lca(x, y, jump, depth)];
}
    
int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<vector<int>>adj(n), jump(n);
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a - 1].push_back(b - 1);
        adj[b - 1].push_back(a - 1);
    }
    vector<int>pre(n), depth(n, 0);
    int t = 0;
    DFS(0, -1, adj, jump, pre, depth, t);
    
    vector<int>color(n);
    for(int &x : color)
        cin >> x;
    
    const int MAX_C = 100'007;
    
    vector<set<pair<int, int>>>s(MAX_C);
    vector<int>answer(MAX_C);
    
    for(int i = 0; i < n; i++) {
        s[color[i]].insert(make_pair(pre[i], i));
    }
    
    for(int i = 0; i < MAX_C; i++) {
        if(s[i].empty())
            continue;
        int last = s[i].rbegin() -> second;
        for(auto [p, x] : s[i]) {
            answer[i] += dist(last, x, jump, depth);
            last = x;
        }
    }
    
    int m; cin >> m;
    for(int i = 0; i < m; i++) {
        char c; cin >> c;
        if(c == 'U') {
            int x, y; cin >> x >> y; x--;
            
            {
                int c = color[x];
                auto it = s[c].find(make_pair(pre[x], x));
                auto next = it; next++;
                if(next == s[c].end())
                    next = s[c].begin();
                auto prev = it;
                if(prev == s[c].begin()) {
                    prev = s[c].end();
                }
                prev--;
                answer[c] -= dist(x, next -> second, jump, depth);
                answer[c] -= dist(x, prev -> second, jump, depth);
                answer[c] += dist(next -> second, prev -> second, jump, depth);
                s[c].erase(it);
            }
            
            {
                
                if(!s[y].empty()) {
                    auto it = s[y].lower_bound(make_pair(pre[x], x));
                    auto next = it;
                    if(it == s[y].end())
                        next = s[y].begin();
                    auto prev = it;
                    if(it == s[y].begin()) {
                        prev = s[y].end();
                    }
                    prev--;
                    
                    answer[y] -= dist(next -> second, prev -> second, jump, depth);
                    answer[y] += dist(next -> second, x, jump, depth);
                    answer[y] += dist(prev -> second, x, jump, depth);
                }
                
                
                color[x] = y;
                s[y].insert(make_pair(pre[x], x));
            }
            
        } else {
            int y; cin >> y;
            if(s[y].size() == 0)
                cout << "-1\n";
            else
                cout << answer[y] / 2 << '\n';
        }
    }
}
