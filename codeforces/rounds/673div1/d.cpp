#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n, m, q; cin >> n >> m >> q;
    vector<int>p(n);
    for(int i = 0; i < n; i++)
        cin >> p[i];
    vector<pair<int, int>>edges(m);
    for(int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
        edges[i].first--; edges[i].second--;
    }
    vector<bool>edgeRemoved(m, false);
    vector<pair<int, int>>queries;
    for(int i = 0; i < q; i++) {
        int x, y; cin >> x >> y;
        queries.emplace_back(y - 1, x - 1);
        if(x == 2) {
            edgeRemoved[y - 1] = true;
        }
    }
    
    for(int i = 0; i < m; i++) {
        if(!edgeRemoved[i]) {
            queries.emplace_back(i, 1);
        }
    }
    
    reverse(queries.begin(), queries.end());
    
    vector<int>f(n);
    for(int i = 0; i < n; i++)
        f[i] = i;
    
    function<int(int)>Find = [&](int x) {
        return f[x] == x ? x : f[x] = Find(f[x]);
    };
    
    vector<set<pair<int, int>>>labelsAndNodes(n);
    for(int i = 0; i < n; i++)
        labelsAndNodes[i].insert(make_pair(-p[i], i));
    
    for(auto &[index, type] : queries) {
        if(type == 1) {
            int a = edges[index].first, b = edges[index].second;
            a = Find(a), b = Find(b);
            if(a != b) {
                if(labelsAndNodes[a].size() < labelsAndNodes[b].size()) {
                    swap(a, b);
                    swap(edges[index].first, edges[index].second);
                }
                edges[index].second = b;
                for(auto p : labelsAndNodes[b]) {
                    f[p.second] = a;
                    labelsAndNodes[a].insert(p);
                }
            } else {
                type = -1;
            }
            
        }
    }
    
    reverse(queries.begin(), queries.end());
    
    for(auto [index, type] : queries) {
        if(type == 0) {
            index = Find(index);
            if(labelsAndNodes[index].size() == 0) {
                cout << "0\n";
            } else {
                int node = labelsAndNodes[index].begin() -> second;
                labelsAndNodes[index].erase(labelsAndNodes[index].begin());
                cout << p[node] << '\n';
                p[node] = 0;
            }
            
        } else if(type == 1) {
            int a = edges[index].first, b = edges[index].second;
            a = Find(a);
            set<pair<int, int>>dummy;
            for(auto pa : labelsAndNodes[b]) {
                f[pa.second] = b;
                if(p[pa.second] == 0)
                    continue;
                auto it = labelsAndNodes[a].find(make_pair(-p[pa.second], pa.second));
                labelsAndNodes[a].erase(it);
                dummy.insert(make_pair(-p[pa.second], pa.second));
            }
            swap(dummy, labelsAndNodes[b]);
        }
    }
    
    return 0;
}
