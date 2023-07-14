#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <queue>
#include <stack>
#include <cstring>
#include <cmath>

using namespace std;

const int MAX_N = 300'000;
vector<int>adj[MAX_N];
multiset<int>s[MAX_N];
int allXor[MAX_N];
int v[MAX_N], n;

int DFS(int x, int p) {
    s[x].insert(v[x]);
    if(adj[x].size() == 1 && p != -1) {
        return 0;
    }
    int result = 0;
    bool cut = false;
    for(int y : adj[x]) {
        if(y == p)
            continue;
        
        result += DFS(y, x);
        
        if(s[y].size() > s[x].size()) {
            swap(s[y], s[x]);
            swap(allXor[x], allXor[y]);
            allXor[x] ^= v[x];
            allXor[y] ^= v[x];
        }
        
        for(int t : s[y]) {
            t ^= allXor[y];
            if(s[x].find(t ^ allXor[x]) != s[x].end()) {
                cut = true;
            }
        }
        for(int t : s[y]) {
            t ^= allXor[y];
            s[x].insert(t ^ v[x] ^ allXor[x]);
        }
        
        
    }
    
    if(cut) {
        s[x].clear();
        result++;
    }
    return result;
}

void TestCase() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", &v[i]);
    for(int i = 0; i < n - 1; i++) {
        int x, y; scanf("%d%d", &x, &y);
        adj[x - 1].emplace_back(y - 1);
        adj[y - 1].emplace_back(x - 1);
    }
    
    int result = DFS(0, -1);
    printf("%d\n", result);
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
