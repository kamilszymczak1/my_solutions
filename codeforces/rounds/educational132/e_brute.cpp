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

const int MAX_N = 20;
vector<int>adj[MAX_N];
multiset<int>s[MAX_N];
int v[MAX_N], n, off[MAX_N];

int popcount(int x) {
    if(x == 0)
        return 0;
    return __builtin_popcount(x);
}

bool DFS(int x, int p, int k) {
    if(k == 0)
        return false;
    for(int y : adj[x]) {
        if(y == p || off[y])
            continue;
        if(!DFS(y, x, k ^ v[y]))
            return false;
    }
    return true;
}

bool Check() {
    for(int i = 0; i < n; i++) {
        if(off[i])
            continue;
        if(!DFS(i, -1, v[i]))
            return false;
    }
    return true;
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
    
    int result = n;
    for(int i = 0; i < (1 << n); i++) {
        for(int j = 0; j < n; j++)
            off[j] = (i >> j) & 1;
        
        if(Check()) {
            //printf("ok %s\n", bitset<5>(i).to_string().c_str());
            result = min(result, popcount(i));
        }
    }
    printf("%d\n", result);
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
