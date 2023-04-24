#include <iostream>
#include <vector>
#include <queue>
#define MAX_N 100
#define inf 1000000000

using namespace std;

struct Edge {
    int to, w;
    Edge(int a, int b) { to = a; w = b; }
};

vector<Edge>graph[MAX_N];
int max_flow[MAX_N][MAX_N];
int flow[MAX_N];
int n;
int q;

inline void load();
inline void find_flow(int s);
inline void answer();

int main() {
    ios_base::sync_with_stdio(0);
    load();
    for(int i = 0; i < n; i++) {
        find_flow(i);
    }
    answer();
    return 0;
}

inline void find_flow(int s) {
    for(int i = 0; i < n; i++) flow[i] = 0;
    flow[s] = inf;
    queue<int>q;
    q.push(s);
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        for(Edge e : graph[x]) {
            if(min(flow[x], e.w) > flow[e.to]) {
                flow[e.to] = min(flow[x], e.w);
                q.push(e.to);
            }
        }
    }
    flow[s] = 0;
    for(int i = 0; i < n; i++) {
        max_flow[s][i] = flow[i];
    }
}

inline void answer() {
    int q, a, b;
    cin >> q;
    for(int i = 0; i < q; i++) {
        cin >> a >> b;
        cout << max_flow[a - 1][b - 1] << "\n";
    }
}

inline void load() {
    int x, a, w;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> x;
        for(int j = 0; j < x; j++) {
            cin>> a >> w; a--;
            graph[i].push_back(Edge(a, w));
        }
    }
}
