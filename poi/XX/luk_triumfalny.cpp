#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 300000;

vector<int>graph[MAX_N];
int g[MAX_N];
int n;

void ReadData();
void DFS(int x, int amount, int p);
int Solve();

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    int result = Solve();
    
    cout << result << '\n';
    
    return 0;
}

void DFS(int x, int amount, int p) {
    g[x] = 0;
    for(int y : graph[x]) {
        if(y == p)
            continue;
        DFS(y, amount, x);
        g[x] += g[y] + 1;
    }
    g[x] = max(0, g[x] - amount);
}

int Solve() {
    int lo = 0, hi = n - 1;
    
    while(lo <= hi) {
        int mid = (lo + hi) / 2;
        DFS(0, mid, -1);
        if(g[0] == 0)
            hi = mid - 1;
        else
            lo = mid + 1;
    }
    return lo;
}

void ReadData() {
    int a, b;
    cin >> n;
    for(int i = 1; i < n; i++) {
        cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }
}
