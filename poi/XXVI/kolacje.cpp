#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct SparseTable {
    vector<vector<int>>values;
    SparseTable() {}
    SparseTable(vector<int>&v) {
        int n = v.size();
        values.resize(n);
        for(int i = 0; i < n; i++)
            values[i].push_back(v[i]);
        
        for(int t = 1; (1 << t) <= n; t++) {
            for(int i = 0; i + (1 << t) <= n; i++) {
                values[i].push_back(min(values[i][t - 1], values[i + (1 << (t - 1))][t - 1]));
            }
        }
    }
    int GetMin(int a, int b) { // m
        long long len = b - a + 1;
        int bit = 31 - __builtin_clz(len);
        return min(values[a][bit], values[b - (1 << bit) + 1][bit]);
    }
};

vector<vector<vector<long long>>>minDistOnPath;
vector<int>depth, nodeByPreorder, firstPreorder, preorder;
vector<long long>distToRoot;
vector<vector<int>>jump;
int _time = 0;
SparseTable S;

const int T = 5500;

void CalcDist(vector<int>&start, vector<vector<pair<int, int>>>&adj, vector<long long>&dist) {
    priority_queue<pair<long long, int>, vector<pair<long long, int>>>q;
    fill(dist.begin(), dist.end(), 1ll << 60);
    for(int x : start)
        dist[x] = 0;
    int n = adj.size();
    for(int i = 0; i < n; i++)
        q.push(make_pair(dist[i], i));
    while(!q.empty()) {
        int x = q.top().second;
        long long d = q.top().first;
        q.pop();
        if(dist[x] != d)
            continue;
        for(auto [y, w] : adj[x]) {
            if(dist[y] > dist[x] + w) {
                dist[y] = dist[x] + w;
                q.push(make_pair(dist[y], y));
            }
        }
    }
}

void DFS(int x, vector<vector<pair<int, int>>>&adj, vector<int>&traverse) {
    nodeByPreorder[_time] = x;
    preorder[x] = _time++;
    firstPreorder[x] = traverse.size();
    traverse.push_back(preorder[x]);
    for(int i = (int)jump[x].size() - 1; i >= 0 && i < (int)jump[x].size(); i++) {
        if(jump[jump[x][i]].size() > i) {
            jump[x].push_back(jump[jump[x][i]][i]);
        }
    }
    for(auto [y, w] : adj[x]) {
        if(depth[y] > depth[x] + 1) {
            depth[y] = depth[x] + 1;
            distToRoot[y] = distToRoot[x] + w;
            jump[y].push_back(x);
            DFS(y, adj, traverse);
            traverse.push_back(preorder[x]);
        }
    }
}

int LCA(int x, int y) {
    x = firstPreorder[x], y = firstPreorder[y];
    if(x > y)
        swap(x, y);
    return nodeByPreorder[S.GetMin(min(x, y), max(x, y))];
}

long long Dist(int x, int y) {
    return distToRoot[x] + distToRoot[y] - 2 * distToRoot[LCA(x, y)];
}

void CalcJump(int x, int p, vector<vector<pair<int, int>>>&adj) {
    if(p != -1) {
        long long value = min(minDistOnPath.back()[x][0], minDistOnPath.back()[p][0]);
        minDistOnPath.back()[x].push_back(value);
    }
    for(int i = 2; i <= jump[x].size(); i++) {
        long long value = minDistOnPath.back()[x][i - 1];
        value = min(value, minDistOnPath.back()[jump[x][i - 2]][i - 1]);
        minDistOnPath.back()[x].push_back(value);
    }
    for(auto [y, w] : adj[x]) {
        if(y != p) {
            CalcJump(y, x, adj);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, r; cin >> n >> r;
    vector<vector<int>>stopsWithLabel(r);
    for(int i = 0; i < n; i++) {
        int label; cin >> label;
        stopsWithLabel[label - 1].push_back(i);
    }
    
    vector<vector<pair<int, int>>>adj(n);
    for(int i = 0; i < n - 1; i++) {
        int x, y, c; cin >> x >> y >> c;
        adj[x - 1].emplace_back(y - 1, c);
        adj[y - 1].emplace_back(x - 1, c);
    }
    
    vector<int>traverse;
    
    depth.resize(n, 1 << 30);
    distToRoot.resize(n, 1ll << 60);
    depth[0] = distToRoot[0] = 0;
    jump.resize(n);
    preorder.resize(n);
    firstPreorder.resize(n);
    nodeByPreorder.resize(n);
    DFS(0, adj, traverse);
    
    S = SparseTable(traverse);
    
    vector<int>labelId(r, -1);
    int lastId = -1;
    for(int i = 0; i < r; i++) {
        if(stopsWithLabel[i].size() >= T) {
            labelId[i] = ++lastId;
            vector<long long>dist(n);
            CalcDist(stopsWithLabel[i], adj, dist);
            
            minDistOnPath.push_back(vector<vector<long long>>(n));
            for(int i = 0; i < n; i++)
                minDistOnPath.back()[i].push_back(dist[i]);
            CalcJump(0, -1, adj);
        }
    }
    
    int q; cin >> q;
    while(q--) {
        int x, y, s; cin >> x >> y >> s; x--; y--; s--;
        long long result = 1ll << 60;
        if(labelId[s] == -1) {
            for(int stop : stopsWithLabel[s]) {
                result = min(result, Dist(x, stop) + Dist(y, stop));
            }
        } else {
            long long distxy = Dist(x, y);
            int id = labelId[s];
            result = 2 * min(minDistOnPath[id][x][0], minDistOnPath[id][y][0]);
            if(depth[x] < depth[y])
                swap(x, y);
            for(int i = (int)jump[x].size() - 1; i >= 0; i--) {
                if(i < (int)jump[x].size() && depth[jump[x][i]] >= depth[y]) {
                    result = min(result, 2 * minDistOnPath[id][x][i + 1]);
                    x = jump[x][i];
                }
            }
            if(x == y) {
                result = min(result, 2 * minDistOnPath[id][x][0]);
            } else {
                for(int i = (int)jump[x].size() - 1; i >= 0; i--) {
                    if(i < (int)jump[x].size() && jump[x][i] != jump[y][i]) {
                        result = min(result, 2 * minDistOnPath[id][x][i + 1]);
                        result = min(result, 2 * minDistOnPath[id][y][i + 1]);
                        x = jump[x][i];
                        y = jump[y][i];
                    }
                }
                x = jump[x][0];
                result = min(result, 2 * minDistOnPath[id][x][0]);
            }
            result += distxy;
        }
        
        cout << (result == (1ll << 60) ? -1 : result) << '\n';
    }
    
    return 0;
}
