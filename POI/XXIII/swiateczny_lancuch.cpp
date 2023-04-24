#include <iostream>
#include <vector>

#define MAX_N 500000
#define log2MN 20

using namespace std;

vector<int>graph[log2MN][MAX_N];
bool visited[log2MN][MAX_N];
int n, m;

void ReadData();
void DFS(int x, int l);
void DFSCheck(int x);

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    for(int i = log2MN - 1; i > 0; i--)
        for(int j = 0; j < n; j++)
            if(!visited[i][j])
                DFS(j, i);
    
    int result = 0;
    for(int i = 0; i < n; i++)
        if(!visited[0][i])
            DFSCheck(i), result++;
    
    cout << result << "\n";
    
    return 0;
}

void DFSCheck(int x) {
    visited[0][x] = true;
    for(int y : graph[0][x])
        if(!visited[0][y])
            DFSCheck(y);
}

void DFS(int x, int l) {
    visited[l][x] = true;
    for(int y : graph[l][x]) {
        if(!visited[l][y]) {
            graph[l - 1][x].push_back(y);
            graph[l - 1][y].push_back(x);
            graph[l - 1][x + (1 << (l - 1))].push_back(y + (1 << (l - 1)));
            graph[l - 1][y + (1 << (l - 1))].push_back(x + (1 << (l - 1)));
            DFS(y, l);
        }
    }
}

void ReadData() {
    int a, b, l;
    cin >> n >> m;
    
    for(int i = 0; i < m; i++) {
        cin >> a >> b >> l;
        a--; b--;
        int additional = 0;
        for(int i = log2MN - 1; i >= 0; i--) {
            if(((1 << i) & l) != 0) {
                graph[i][a + additional].push_back(b + additional);
                graph[i][b + additional].push_back(a + additional);
                additional += (1 << i);
            }
        }
    }
}
