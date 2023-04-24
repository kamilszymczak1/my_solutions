#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

const int B = 62;

struct Trie {
    struct Node {
        int child[2], info;
        Node() { 
            child[0] = child[1] = -1;
            info = 0;
        };
    };
    vector<Node>nodes;
    int NewNode() {
        nodes.emplace_back();
        return (int)nodes.size() - 1;
    }
    Trie() {nodes = {Node()}; }
    void Add(long long x, int info) {
        int node = 0;
        for(int i = B - 1; i >= 0; i--) {
            if(nodes[node].child[(x >> i) & 1] == -1) {
                int t = NewNode();
                nodes[node].child[(x >> i) & 1] = t;
            }
            node = nodes[node].child[(x >> i) & 1];
        }
        nodes[node].info = info;
    }
    int GetInfoOfMax(long long x) {
        int node = 0;
        for(int i = B - 1; i >= 0; i--) {
            if(nodes[node].child[((x >> i) & 1) ^ 1] == -1) {
                node = nodes[node].child[(x >> i) & 1];
            } else {
                node = nodes[node].child[((x >> i) & 1) ^ 1];
            }
        }
        return nodes[node].info;
    }
};

bool Match(vector<vector<int>>&adj, vector<int>&matching) {
    int n = adj.size() / 2;
    fill(matching.begin(), matching.end(), -1);
    vector<int>parent(n * 2);
    bool found;
    do {
        fill(parent.begin(), parent.end(), -1);
        found = false;
        for(int i = 0; i < n; i++) {
            if(matching[i] != -1 || parent[i] >= 0)
                continue;
            queue<int>q;
            parent[i] = -2;
            for(q.push(i); !q.empty(); q.pop()) {
                int x = q.front();
                if(x >= n) {
                    if(matching[x] == -1) {
                        while(x != -2) {
                            matching[x] = parent[x];
                            matching[parent[x]] = x;
                            x = parent[parent[x]];
                        }
                        found = true;
                        break;
                    } else {
                        if(parent[matching[x]] == -1) {
                            parent[matching[x]] = x;
                            q.push(matching[x]);
                        }
                    }
                } else {
                    for(int y : adj[x]) {
                        if(parent[y] == -1) {
                            parent[y] = x;
                            q.push(y);
                        }
                    }
                }
            }
        }
    } while(found);
    return *min_element(matching.begin(), matching.end()) >= 0;
}

int main() {
    int n; scanf("%d", &n);
    array<vector<long long>, 2>a;
    array<Trie, 2>T;
    for(int k = 0; k < 2; k++) {
        a[k].resize(n);
        for(int i = 0; i < n; i++) {
            scanf("%lld", &a[k][i]);
            T[k].Add(a[k][i], i);
        }
    }
    
    vector<vector<int>>adj(n * 2);
    for(int k = 0; k < 2; k++) {
        for(int i = 0; i < n; i++) {
            int another = T[k ^ 1].GetInfoOfMax(a[k][i]);
            adj[i + n * (k & 1)].push_back(another + n * ((k & 1) ^ 1));
            adj[another + n * ((k & 1) ^ 1)].push_back(i + n * (k & 1));
        }
    }
    
    vector<int>matching(n * 2);
    if(Match(adj, matching)) {
        printf("TAK\n");
        for(int i = 0; i < n; i++)
            printf("%d ", matching[i] - n + 1);
        printf("\n");
    } else {
        printf("NIE\n");
    }
}
