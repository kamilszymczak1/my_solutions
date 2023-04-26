#include <cstdio>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX_N = 10'000;
const int inf = 100'000;

const int MAX_NODES = MAX_N * 2 + 3;

struct edge {
    int to, from, cap;
    edge(int _to, int _from, int _cap) : to(_to), from(_from), cap(_cap) {}
    edge() {}
};

vector<edge>edges;
vector<int>adj[MAX_NODES];
int n, m, s[MAX_N], a[MAX_N], in_deg[MAX_N], parent[MAX_NODES], visited[MAX_NODES];
int iteration = -1;
pair<int, int>e[MAX_N];

void add_edge(int x, int y, int c) {
    adj[x].push_back(edges.size());
    edges.emplace_back(y, x, c);
    adj[y].push_back(edges.size());
    edges.emplace_back(x, y, 0);
}

int dfs_find(int x, int f, int t) {
    visited[x] = iteration;
    if(x == t)
        return f;
    for(int e_id : adj[x]) {
        int my_f = edges[e_id].cap;
        int y = edges[e_id].to;
        if(visited[y] != iteration && my_f > 0) {
            parent[y] = e_id;
            int ret = dfs_find(y, min(my_f, f), t);
            if(ret != 0)
                return ret;
        }
    }
    return 0;
}

int push_flow(int s, int t) {
    iteration++;
    parent[s] = -1;
    return dfs_find(s, inf, t);
}

int max_flow(int s, int t) {
    int f = 0, delta_f = push_flow(s, t);
    while(delta_f != 0) {
        f += delta_f;
        for(int x = t; x != s; x = edges[parent[x]].from) {
            int y = edges[parent[x]].from;
            int e_id = parent[x];
            edges[e_id ^ 0].cap -= delta_f;
            edges[e_id ^ 1].cap += delta_f;
        }
        delta_f = push_flow(s, t);
    }
    return f;
}

int main() {
    fill(visited, visited + MAX_NODES, -1);
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++)
        scanf("%d", &s[i]);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    
    
    for(int i = 0; i < m; i++) {
        add_edge(0, i + 1, 1);
        scanf("%d%d", &e[i].first, &e[i].second);
        e[i].first--; e[i].second--;
        in_deg[e[i].first]++;
        in_deg[e[i].second]++;
        add_edge(i + 1, e[i].first + m + 1, 1);
        add_edge(i + 1, e[i].second + m + 1, 1);
    }
    
    int total_out = m, total_in = 0;
    
    for(int i = 0; i < n; i++) {
        if(s[i] != 0) {
            if(abs(in_deg[i] + a[i]) % 2 == 1) {
                printf("NO\n");
                return 0;
            } else {
                total_in += (in_deg[i] + a[i]) / 2;
                add_edge(i + m + 1, m + n + 1, (in_deg[i] + a[i]) / 2);
            }
        } else {
            add_edge(i + m + 1, m + n + 2, inf);
        }
    }
    
    if(total_out < total_in) {
        printf("NO\n");
        return 0;
    } else {
        add_edge(n + m + 2, n + m + 1, total_out - total_in);
    }
    
    int f = max_flow(0, n + m + 1);
    
    for(int i = 0; i < n; i++) {
        if(s[i] != 0) {
            for(int e_id : adj[i + m + 1]) {
                if(edges[e_id].to == n + m + 1 && edges[e_id].cap != 0) {
                    printf("NO\n");
                    return 0;
                }
            }
        }
    }
    
    if(f != m) {
        printf("NO\n");
    } else {
        printf("YES\n");
        for(int i = 0; i < m; i++) {
            bool printed = false;
            for(int e_id : adj[i + 1]) {
                if(edges[e_id].to == e[i].first + m + 1) {
                    
                    if(edges[e_id].cap == 0) {
                        printf("%d %d\n", e[i].second + 1, e[i].first + 1);
                    } else {
                        printf("%d %d\n", e[i].first + 1, e[i].second + 1);
                    }
                    
                    printed = true;
                    break;
                }
                if(printed)
                    break;
            }
        }
    }
    
    return 0;
}
