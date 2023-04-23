#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <queue>
#include <list>

const int inf = 1 << 30;
const int MAX_N = 100'007;

using namespace std;

struct Node {
    int a, b;
    Node() {}
    Node(int _a, int _b) : a(_a), b(_b) {}
};

void BFS(int s, vector<set<int>>&adj, vector<int>&result, int a) {
    queue<int>q;
    result[s] = 0;
    for(q.push(s); !q.empty(); q.pop()) {
        int x = q.front(); 
        for(int y : adj[x]) {
            if(result[y] > result[x] + a) {
                result[y] = result[x] + a;
                q.push(y);
            }
        }
    }
}

int main() {
    int n, m, k, a, b; scanf("%d%d%d%d%d", &n, &m, &k, &a, &b); k--;
    vector<pair<int, int>>E(m * 2);
    vector<vector<int>>D(m * 2, vector<int>(2, inf));
    vector<vector<list<int>>>adj(n, vector<list<int>>(2));
    vector<set<int>>allAdj(n);
    vector<int>result(n, inf);
    for(int i = 0; i < m; i++) {
        int x, y; scanf("%d%d", &x, &y); x--; y--;
        E[i * 2] = make_pair(x, y);
        E[i * 2 + 1] = make_pair(y, x);
        for(int j = 0; j < 2; j++) {
            adj[x][j].push_back(i * 2);
            adj[y][j].push_back(i * 2 + 1);
        }
        allAdj[x].insert(y);
        allAdj[y].insert(x);
    }
    
    BFS(k, allAdj, result, a);
    
    queue<Node>q;
    for(int e : adj[k][0]) {
        q.push(Node(e, 1));
        D[e][1] = 1;
    }
    
    for(; !q.empty(); q.pop()) {
        Node x = q.front();
        for(auto it = adj[E[x.a].second][x.b].begin(); it != adj[E[x.a].second][x.b].end(); ) {
            if(allAdj[E[x.a].first].find(E[*it].second) != allAdj[E[x.a].first].end() && x.b == 1) {
                it++;
            } else {
                D[*it][x.b ^ 1] = D[x.a][x.b] + 1;
                q.push(Node(*it, x.b ^ 1));
                it = adj[E[x.a].second][x.b].erase(it);
            }
        }
    }
    
    
    for(int i = 0; i < m * 2; i++) {
        if(D[i][0] == inf)
            continue;
        result[E[i].second] = min(result[E[i].second], (D[i][0] / 2) * b);
    }
    
    for(int i = 0; i < n; i++)
        for(int j : allAdj[i])
            result[i] = min(result[i], result[j] + a);
    
    for(int i = 0; i < n; i++)
        printf("%d\n", result[i]);
        
    return 0;
}
