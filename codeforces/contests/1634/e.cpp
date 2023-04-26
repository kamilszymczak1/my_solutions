#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

int Scale(vector<vector<int>>&a) {
    vector<int>values;
    for(vector<int>&v : a)
        for(int x : v)
            values.push_back(x);
        map<int, int>m;
    sort(values.begin(), values.end());
    int k = 0;
    m[values[0]] = k++;
    for(int i = 1; i < (int)values.size(); i++)
        if(values[i] != values[i - 1])
            m[values[i]] = k++;
        for(vector<int>&v : a)
            for(int &x : v)
                x = m[x];
            return k;
}

void DFS(int x, vector<set<pair<int, int>>>&adj, vector<vector<bool>>&ans, int m) {
    if(!adj[x].empty()) {
        pair<int, int>p = *adj[x].begin();
        adj[x].erase(adj[x].begin());
        adj[p.first].erase(adj[p.first].find(make_pair(x, p.second)));
        
        if(x < m) {
            ans[x][p.second] = true;
        } else {
            ans[p.first][p.second] = false;
        }
        
        
        DFS(p.first, adj, ans, m);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int m; cin >> m;
    vector<vector<int>>a(m);
    for(int i = 0; i < m; i++) {
        int n; cin >> n;
        a[i].resize(n);
        for(auto &x : a[i])
            cin >> x;
    }
    int k = Scale(a);
    
    vector<set<pair<int, int>>>adj(k + m);
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < (int)a[i].size(); j++) {
            adj[i].insert(make_pair(a[i][j] + m, j));
            adj[a[i][j] + m].insert(make_pair(i, j));
        }
    }
    
    for(int i = 0; i < m + k; i++) {
        if(adj[i].size() % 2 == 1) {
            cout << "NO\n";
            return 0;
        }
    }
    
    vector<vector<bool>>ans(m);
    for(int i = 0; i < m; i++)
        ans[i].resize(a[i].size());
    
    for(int i = 0; i < m + k; i++) {
        if(!adj[i].empty()) {
            DFS(i, adj, ans, m);
        }
    }
    
    cout << "YES\n";
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < (int)ans[i].size(); j++) {
            cout << (ans[i][j] ? 'L' : 'R');
        }
        cout << '\n';
    }
    
    return 0;
}
