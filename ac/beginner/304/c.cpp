#include <iostream>

using namespace std;

const int MAX_N = 2000;

int x[MAX_N], y[MAX_N], visited[MAX_N], n, d;

void dfs(int j) {
    visited[j] = 1;
    for(int i = 0; i < n; i++) {
        if(visited[i] == 1)
            continue;
        
        int dx = x[i] - x[j];
        int dy = y[i] - y[j];
        
        if(dx * dx + dy * dy <= d * d) {
            dfs(i);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> d;
    for(int i = 0; i < n; i++)
        cin >> x[i] >> y[i];
    
    dfs(0);
    
    for(int i = 0; i < n; i++)
        cout << (visited[i] ? "Yes" : "No") << '\n';
    
    return 0;
}
