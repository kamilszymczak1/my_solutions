#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 100000;

enum Color {WHITE, RED, BLACK};

int t[MAX_N], T[MAX_N], M[MAX_N], n;
vector<int>sorted, graph[MAX_N], graphT[MAX_N];
Color c[MAX_N];

void ReadData();
bool topoSort(), DFS(int x);

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    int a, addT, k;
    
    fill(c, c + n, WHITE);
    
    if(topoSort()) {
        
        int greatestT = 0;
        for(int i = n - 1; i >= 0; i--)
            for(int y : graph[sorted[i]])
                greatestT = max((T[y] = max(T[y], t[sorted[i]] + T[sorted[i]])) + t[y], greatestT);
            
        for(int i = 0; i < n; i++)
            M[i] = greatestT - t[i];
        
        for(int i = 0; i < n; i++)
            for(int y : graphT[sorted[i]])
                M[y] = min(M[y], M[sorted[i]] - t[y]);
            
        cout << greatestT << "\n";    
        cin >> k;
        while(k--) {
            cin >> a >> addT;
            cout << (addT <= M[a - 1] - T[a - 1] ? "NIE" : "TAK") << "\n";
        }
        
    } else
        cout << "CYKL\n";
    
    return 0;
}

bool topoSort() {
    for(int i = 0; i < n; i++)
        if(c[i] == WHITE && !DFS(i))
            return false;
    return true;
}

bool DFS(int x) {
    if(c[x] == RED)
        return false;
    if(c[x] == BLACK)
        return true;
    c[x] = RED;
    for(int y : graph[x])
        if(!DFS(y))
            return false;
    sorted.push_back(x);
    c[x] = BLACK;
    return true;
}

void ReadData() {
    int k, a;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> t[i] >> k;
        while(k--) {
            cin >> a;
            graph[a - 1].push_back(i);
            graphT[i].push_back(a - 1);
        }
    }
}
