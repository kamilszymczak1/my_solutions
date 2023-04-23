#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
long long nextInt() {long long x; cin >> x; return x;}
const int MAX_N = 1000007;
vector<int>graph[MAX_N];
long long subtree[MAX_N], h[MAX_N], n;
bool special[MAX_N];

long long DFS1(int x, int p) {
    special[x] = true;
    subtree[x] = 1;
    for(int y : graph[x]) {
        if(y == p)
            continue;
        long long ySubtree = DFS1(y, x);
        subtree[x] += ySubtree;
        if(2 * ySubtree > n)
            special[x] = false;
    }
    if(2 * (n - subtree[x]) > n)
        special[x] = false;
    return subtree[x];
}

long long DFS2(int x, int p) {
    subtree[x] = 1;
    long long result = 0;
    h[x] = 0;
    for(int y : graph[x]) {
        if(y == p)
            continue;
        result += DFS2(y, x);
        subtree[x] += subtree[y];
        result += subtree[y] * 2;
        h[x] = max(h[x], h[y] + 1);
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    n = nextInt();
    for(int i = 1; i < n; i++) {
        int a = nextInt() - 1, b = nextInt() - 1;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    DFS1(0, -1);
    for(int x = 0; x < n; x++)
        if(special[x]) {
            long long total = h[x] = 0;
            bool requiredH = false;
            for(int y : graph[x]) {
                total += DFS2(y, x);
                total += subtree[y] * 2;
                if(2 * subtree[y] == n) {
                    h[x] = h[y] + 1;
                    requiredH = true;
                }
                if(!requiredH)
                    h[x] = max(h[x], h[y] + 1);
            }
            cout << total - h[x] << '\n';
        } else {
            cout << "-1\n";
        }
        
        return 0;
}
