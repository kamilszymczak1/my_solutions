#include <iostream> 
#include <queue>
#include <vector>
#include <set>
#define MAX_N 5000
#define inf 1000000000000000000

using namespace std;

struct Edge {
    int to;
    long long w;
    Edge(int a, long long b) {
        to = a;
        w = b;
    }
};

long long cost[MAX_N];
long long dist[2][MAX_N];
vector<Edge>graph[2][MAX_N];
int n;
int curr = 0;

struct Comp {
    inline bool operator() (int a, int b) const {
        if(dist[curr][a] == dist[curr][b]) return a < b;
        return dist[curr][a] < dist[curr][b];
    }
};

void Load();
long long FindBestCost();
void Dijkstra(int num);

int main() {
    ios_base::sync_with_stdio(0);
    
    Load();
    
    long long result = FindBestCost();
    
    cout << result << "\n";
    
    return 0;
}

long long FindBestCost() {
    
    for(int i = 0; i < 2; i++)
        Dijkstra(i);
    
    long long result = inf;
    
    for(int i = 0; i < n; i++)
        result = min(result, dist[0][i] + dist[1][i] + cost[i]);
    
    return result;
}

void Dijkstra(int x) {
    
    curr = x;
    
    set<int, Comp>bag;
    dist[x][0] = 0;
    bag.insert(0);
    for(int i = 1; i < n; i++) {
        dist[x][i] = inf;
        bag.insert(i);
    }
    
    while(!bag.empty()) {
        int v = *(bag.begin());
        bag.erase(bag.begin());
        
        for(Edge e : graph[x][v]) {
            if(dist[x][v] + e.w < dist[x][e.to]) {
                bag.erase(bag.find(e.to));
                dist[x][e.to] = dist[x][v] + e.w;
                bag.insert(e.to);
            }
        }
    }
}

void Load() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> cost[i];
        cost[i] >>= 1;
    }
    int m, a, b;
    long long w;
    cin >> m;
    
    for(int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        a--; b--;
        graph[0][a].push_back(Edge(b, w));
        graph[1][b].push_back(Edge(a, w));
    }
}
