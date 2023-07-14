#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int MAX_N = 200'007;

vector<int>adj[MAX_N], jump[MAX_N];
vector<pair<int, int>>children[MAX_N];
int depth[MAX_N], pre[MAX_N], post[MAX_N], t = 0, n, q;

void DFS(int x, int p) {
    if(p != -1) {
        jump[x].emplace_back(p);
        for(int i = 0; i < (int)jump[x].size(); i++) {
            if(i < (int)jump[jump[x][i]].size()) {
                jump[x].push_back(jump[jump[x][i]][i]);
            }
        }
    }
    pre[x] = t++;
    for(int y : adj[x]) {
        if(y != p) {
            depth[y] = depth[x] + 1;
            DFS(y, x);
            children[x].emplace_back(post[y], y);
        }
    }
    post[x] = t++;
}

int LCA(int x, int y) {
    if(depth[x] < depth[y])
        swap(x, y);
    for(int i = (int)jump[x].size(); i >= 0; i--) {
        if(i < (int)jump[x].size() && depth[jump[x][i]] >= depth[y]) {
            x = jump[x][i];
        }
    }
    if(x == y)
        return x;
    for(int i = (int)jump[x].size(); i >= 0; i--) {
        if(i < (int)jump[x].size() && jump[x][i] != jump[y][i]) {
            x = jump[x][i];
            y = jump[y][i];
        }
    }
    return jump[x][0];
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i < n; i++) {
        int x, y; scanf("%d%d", &x, &y);
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    
    DFS(0, -1);
    
    scanf("%d", &q);
    while(q--) {
        int k; scanf("%d", &k);
        vector<pair<int, int>>myNodes;
        for(int i = 0; i < k; i++) {
            int x; scanf("%d", &x);
            myNodes.emplace_back(depth[x - 1], x - 1);
        }
        sort(myNodes.begin(), myNodes.end());
        int root = myNodes[0].second;
        for(int i = 0; i < (int)myNodes.size() - 1; i++) {
            int lca = LCA(myNodes[i].second, myNodes[i + 1].second);
            if(depth[lca] < depth[root])
                root = lca;
        }
        if(depth[root] < myNodes[0].first) {
            myNodes.emplace_back(depth[root], root);
            sort(myNodes.begin(), myNodes.end());
        }
        root = myNodes[0].second;
        map<int, vector<int>>m;
        bool answer = true;
        for(int i = 1; i < (int)myNodes.size(); i++) {
            int node = myNodes[i].second;
            int childId = lower_bound(children[root].begin(), children[root].end(), make_pair(post[node], -1)) - children[root].begin();
            m[childId].push_back(node);
            if(m.size() > 2) {
                answer = false;
                break;
            }
        }
        
        if(answer) {
            for(auto [node, vec] : m) {
                reverse(vec.begin(), vec.end());
                vec.push_back(root);
                
                for(int i = 0; i < (int)vec.size() - 1; i++) {
                    int x = vec[i], y = vec[i + 1];
                    if(pre[y] > pre[x] || pre[x] > post[y])
                        answer = false;
                }
            }
        }
        
        printf("%s\n", answer ? "YES" : "NO");
    }
}
