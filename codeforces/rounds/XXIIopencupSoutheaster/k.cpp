#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 200'007;

int n;
vector<int>adj[MAX_N];
bool visited[MAX_N], smallest_leaf[MAX_N];

void calc_smallest_leaf(int x) {
    visited[x] = true;
    if(adj[x].size() == 1) {
        smallest_leaf[x] = x;
        return;
    }
    
    smallest_leaf[x] = n + 1;
    for(int y : adj[x]) {
        if(!visited[y]) {
            calc_smallest_leaf(y);
            smallest_leaf[x] = min(smallest_leaf[x], smallest_leaf[y]);
        }
    }
}

void test_case() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        adj[i].clear();
        visited[i] = false;
    }
    
    for(int i = 1; i < n; i++) {
        int x, y; scanf("%d%d", &x, &y);
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    
    int smallest_leaf = 
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}
