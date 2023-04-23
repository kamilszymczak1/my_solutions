#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 100000;

vector<int>graph[MAX_N];
int dist[MAX_N];
bool visited[MAX_N];
int n, a, b, da, db;

int diameter;

int findDiameter();

bool Query();
void DFS(int x);

int main() {
    ios_base::sync_with_stdio(0);
    
    int t;
    cin >> t;
    
    for(int i = 0; i < t; i++) {
        if(Query())
            cout << "Alice\n";
        else
            cout << "Bob\n";
        for(int i = 0; i < n; i++)
            graph[i].clear();
    }
    
    return 0;
}

bool Query() {
    cin >> n >> a >> b >> da >> db;
    
    int x, y;
    for(int i = 1; i < n; i++) {
        cin >> x >> y;
        graph[x - 1].push_back(y - 1);
        graph[y - 1].push_back(x - 1);
    }
    
    fill(visited, visited + n, false);
    dist[a - 1] = 0;
    DFS(a - 1);
    if(dist[b - 1] <= da)
        return true;
    
    diameter = findDiameter();
    
    if(da * 2 >= diameter || db < da * 2 + 1)
        return true;
    
    return false;
}

int findDiameter() {
    fill(visited, visited + n, false);
    dist[0] = 0;
    DFS(0);
    
    int bestDist = 0, bestIndex = 0;
    for(int i = 0; i < n; i++)
        if(dist[i] > bestDist)
            bestDist = dist[i], bestIndex = i;
    fill(visited, visited + n, false);
    dist[bestIndex] = 0;
    DFS(bestIndex);
    
    int result = 0;
    for(int i = 0; i < n; i++)
        result = max(result, dist[i]);
    return result;
}

void DFS(int x) {
    visited[x] = true;
    for(int y : graph[x])
        if(!visited[y])
            dist[y] = dist[x] + 1, DFS(y);
}
