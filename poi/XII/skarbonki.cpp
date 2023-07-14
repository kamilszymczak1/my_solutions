#include <iostream>
#include <vector>
#include <stack>

#define MAX_N 1000100

using namespace std;

int graph[MAX_N];
int n, currentIndex = 0, result;
int parent[MAX_N];

void ReadData();
void DFS(int v);

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    fill(parent, parent + n, -1);
    
    for(int i = 0; i < n; i++)
        if(parent[i] == -1) {
            DFS(i);
            currentIndex++;
        }
        
    cout << result << "\n";
    
    return 0;
}

void DFS(int v) {
    parent[v] = currentIndex;
    int x = graph[v];
    if(parent[x] == -1)
        DFS(x);
    else if(parent[x] == currentIndex)
        result++;
}

void ReadData() {
    int a;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a;
        graph[i] = a - 1;
    }
}
