#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <bitset>

using namespace std;

void Gather(int x, vector<int>&visited, vector<vector<pair<int, int>>>&adj, vector<int>&nodes) {
    nodes.push_back(x);
    visited[x] = true;
    for(auto [y, id] : adj[x]) {
        if(visited[y])
            continue;
        Gather(y, visited, adj, nodes);
    }
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    vector<vector<pair<int, int>>>adj(n);
    vector<int>p(n), deg(n), visited(n, 0), where(n);
    map<pair<int, int>, int>id;
    for(int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
        p[i]--;
        where[p[i]] = i;
    }
        
    for(int i = 0; i < m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        adj[a - 1].emplace_back(b - 1, i);
        adj[b - 1].emplace_back(a - 1, i);
        id[{a - 1, b - 1}] = id[{b - 1, a - 1}] = i;
        deg[a - 1]++;
        deg[b - 1]++;
    }
    vector<int>order;
    for(int i = 0; i < n; i++) {
        if(visited[i])
            continue;
        vector<int>nodes;
        Gather(i, visited, adj, nodes);
//         printf("nodes = ");
//         for(int x : nodes)
//             printf("%d ", x + 1);
//         printf("\n");
        if(nodes.size() == 2) {
            order.push_back(id[{nodes[0], nodes[1]}]);
            continue;
        }
        vector<pair<int, int>>validSwaps;
        for(int x : nodes) {
            if(deg[x] == 1) {
                //printf("x = %d\n", x + 1);
                for(auto [y, id] : adj[x]) {
                    if(p[y] == x) {
                        //printf("y = %d, p[y] = %d\n", y + 1, p[y] + 1);
                        validSwaps.emplace_back(x, y);
                    }
                }
            }
        }
//         printf("validSwaps = ");
//         for(auto [a, b] : validSwaps)
//             printf("(%d, %d) ", a + 1, b + 1);
//         printf("\n");
        while(!validSwaps.empty()) {
            auto [x, y] = validSwaps.back();
            validSwaps.pop_back();
            order.push_back(id[{x, y}]);
            swap(p[x], p[y]);
            where[p[x]] = x;
            where[p[y]] = y;
            deg[x]--; deg[y]--;
            for(int z : {x, y}) {
                if(deg[z] == 0 || where[z] == z)
                    continue;
                if(deg[z] == 1) { // z is a leaf
                    if(id.find({z, where[z]}) != id.end()) {
                        validSwaps.emplace_back(z, where[z]);
                    }
                } else {
                    if(id.find({z, p[z]}) != id.end() && deg[p[z]] == 1) {
                        validSwaps.emplace_back(z, p[z]);
                    }
                }
                
            }
        }
    }
    
    for(int x : order)
        printf("%d ", x + 1);
    printf("\n");
    
    return 0;
}
