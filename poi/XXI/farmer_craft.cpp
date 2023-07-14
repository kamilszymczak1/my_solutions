#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 500007;
int T[MAX_N], t[MAX_N], c[MAX_N];
vector<int>adj[MAX_N];

bool cmp(int a, int b) {
    if(t[a] >= T[a] + t[b] + 2)
        return true;
    return T[a] + t[b] < T[b] + t[a];
}

void DFS(int x, int p) {
    T[x] = 0, t[x] = c[x];
    vector<int>sons;
    for(int y : adj[x]) {
        if(y != p) {
            DFS(y, x);
            T[x] += T[y] + 2;
            sons.emplace_back(y);
        }
    }
    sort(sons.begin(), sons.end(), cmp);
    int current = 0;
    for(int son : sons) {
        t[x] = max(t[x], current + t[son] + 1);
        current += T[son] + 2;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    for(int i = 0; i < n; i++)
        cin >> c[i];
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a - 1].push_back(b - 1);
        adj[b - 1].push_back(a - 1);
    }
    DFS(0, -1);
    cout << max(t[0], T[0] + c[0]) << '\n';
    return 0;
}
