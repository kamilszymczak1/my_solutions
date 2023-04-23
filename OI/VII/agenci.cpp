#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 250
#define size MAX_N * MAX_N * 2
#define inf 99999999

using namespace std;

vector<int>graph[MAX_N];
bool satisfy[size];
int dist[size];
int n, m, beg;

void ReadData();
int BFS();

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    for(int i = 0; i < n; i++)
        satisfy[i * (n + 1)] = true;
    
    int result = BFS();
    
    if(result == -1)
        cout << "NIE\n";
    else
        cout << result / 2 << "\n";
        
    return 0;
}

int BFS() {
    fill(dist, dist + n * n * 2, inf);
    dist[beg] = 0;
    queue<int>q;
    q.push(beg);
    
    while(!q.empty()) {
        int val = q.front();
        q.pop();
        int v = val;
         
        if(satisfy[val])
            return dist[val];

        int x = val < (n * n) ? 0 : 1;
        
        val = val % (n * n);
        int a[2] = {val / n, val % n};
        
        for(int y : graph[a[x]]) {
            int neighbour = 0;
            if(x == 0)
                neighbour = (y * n) + a[1] + (n * n);
            else
                neighbour = (a[0] * n) + y;
            
            if(dist[neighbour] == inf) {
                dist[neighbour] = dist[v] + 1;
                q.push(neighbour);
            }
        }
        
        
        
    }
    return -1;
}

void ReadData() {
    int a, b;
    cin >> n >> m >> a >> b;
    beg = (a - 1) * n + b - 1;
    for(int j = 0; j < m; j++) {
        cin >> a >> b;
        graph[a - 1].push_back(b - 1);
    }
}
