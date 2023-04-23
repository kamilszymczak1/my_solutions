#include <iostream>
#include <vector>

#define MAX_K 5000
#define MAX_M 300
#define MAX_N 1000
#define MAX_S 2000
#define inf 999999

using namespace std;

struct Edge {
    int to, cost;
    Edge(int a, int b) {
        to = a;
        cost = b;
    }
};

vector<Edge>graph[MAX_N];

bool visited[MAX_S + 1][MAX_N];
int n, n1, k, m, beg, s;
int mergeBase(int x);

void ReadData();
int DFS(int x, int l);

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    int result = DFS(beg, s);
    
    cout << result << "\n";
    
    return 0;
}

int DFS(int x, int l) {
    visited[l][x] = true;
    int result = x < n1 ? l : inf;
    for(Edge e : graph[x]) {
        int newCost = l - e.cost;
        if(newCost >= 0 && !visited[newCost][e.to])
            result = min(DFS(e.to, newCost), result);
    }
    return result;
}

void ReadData() {
    int a, b, c;
    cin >> n >> n1 >> k;
    for(int i = 0; i < k; i++) {
        cin >> a >> b;
        graph[a - 1].push_back(Edge(b - 1, 0));
    }
    cin >> m;
    for(int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        graph[a - 1].push_back(Edge(b - 1, c));
    }
    cin >> beg >> s;
    beg--;
}
