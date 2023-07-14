#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX_N = 3000007;
vector<int>adj[MAX_N];
int deg[MAX_N], n, k;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a - 1].push_back(b - 1);
        adj[b - 1].push_back(a - 1);
        deg[a - 1]++; deg[b - 1]++;
    }
    
    queue<int>leaves;
    for(int i = 0; i < n; i++) {
        if(deg[i] == 1) {
            leaves.push(i);
        }
    }
    
    int r;
    for(r = 0; leaves.size() > k; r++) {
        queue<int>newLeaves;
        for(; !leaves.empty(); leaves.pop()) {
            int x = leaves.front();
            for(int y : adj[x]) {
                deg[y]--;
                if(deg[y] == 1) {
                    newLeaves.push(y);
                }
            }
        }
        swap(leaves, newLeaves);
    }
    
    if(leaves.empty()) {
        leaves.push(0);
        leaves.push(1);
    } else if(leaves.size() == 1) {
        leaves.push(leaves.front() == 0 ? 1 : 0);
    }
    cout << r << ' ' << leaves.size() << '\n';
    for(; !leaves.empty(); leaves.pop())
        cout << leaves.front() + 1 << ' ';
    cout << '\n';
    
    return 0;
}
