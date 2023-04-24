#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 40000

using namespace std;

vector<int>graph[MAX_N];
int dist[2][MAX_N];
int n, m;
int layer[6] = {1, 0, 0, 0, 0, 1};

void ReadData();
void BFS(int beg, int l);

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    for(int i = 0; i < 2; i++)
        BFS(i, i);
    
    int otherNodes = 0;
    
    for(int i = 2; i < n; i++) {
        if(dist[0][i] == 1)
            layer[1]++;
        else if(dist[0][i] == 2)
            layer[2]++;
        else if(dist[1][i] == 2)
            layer[3]++;
        else if(dist[1][i] == 1)
            layer[4]++;
        else
            otherNodes++;
    }
    
    layer[2] += otherNodes;
    
    int totalEdges = 0;
    
    for(int i = 0; i <= otherNodes; i++) {
        int currentTotalEdges = 0;
        for(int j = 0; j < 5; j++)
            currentTotalEdges += (layer[j] * (layer[j] - 1) / 2) + (layer[j] * layer[j + 1]);
        layer[2]--;
        layer[3]++;
        totalEdges = max(totalEdges, currentTotalEdges);
    }
    
    int result = totalEdges - m;
    
    cout << result << "\n";
    
    return 0;
}

void BFS(int beg, int l) {
    fill(dist[l], dist[l] + n, -1);
    dist[l][beg] = 0;
    queue<int>q;
    q.push(beg);
    
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        
        for(int y : graph[x])
            if(dist[l][y] == -1) {
                dist[l][y] = dist[l][x] + 1;
                q.push(y);
            }
    }
}

void ReadData() {
    int a, b;
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }
}
