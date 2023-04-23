#include <algorithm>
#include <cstdio>
#include <vector>
#include <bitset>
using namespace std;
const int MAX_M = 1000007, MAX_N = 500007;
class Tree {
private:
    int leafCount;
    vector<int>val;
public:
    Tree(int n) {
        for(leafCount = 1; leafCount < n; leafCount <<= 1) {}
        val.reserve(leafCount << 1);
        val.resize(leafCount << 1, 0);
    }
    int get(int x) {
        x += leafCount;
        int res = val[x];
        while(x > 1) {
            x >>= 1;
            res = max(res, val[x]);
        }
        return res;
    }
    void insert(int a, int b, int value) {
        a += leafCount;
        b += leafCount;
        val[a] = max(val[a], value);
        val[b] = max(val[b], value);
        for(;(a >> 1) != (b >> 1); a >>= 1, b >>= 1) {
            if(!(a & 1))
                val[a + 1] = max(val[a + 1], value);
            if(b & 1)
                val[b - 1] = max(val[b - 1], value);
        }
    }
};

struct Edge {
    int a, b;
    Edge() {}
    Edge(int _a, int _b) : a(_a), b(_b) {}
};
Edge E[MAX_M];
vector<int>graph[MAX_N];
int e, n, m;
int indexAtTopoOrder[MAX_N], maxBeg[MAX_N], maxEnd[MAX_N]; 
int maxPref[MAX_N], maxSuf[MAX_N], result[MAX_N], topoOrder[MAX_N];
bitset<MAX_N>visited;

void DFS(int x) {
    visited[x] = true;
    for(int e : graph[x]) {
        if(!visited[E[e].b]) {
            DFS(E[e].b);
        }
    }
    topoOrder[e++] = x;
}

void TopoSort() {
    e = 0;
    for(int i = 0; i < n; i++)
        if(!visited[i])
            DFS(i);
    reverse(topoOrder, topoOrder + n);
    for(int i = 0; i < n; i++)
        indexAtTopoOrder[topoOrder[i]] = i;
}

void Read() {
    scanf("%d%d", &n, &m);
    e = 0;
    for(int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        graph[a - 1].push_back(e);
        graph[b - 1].push_back(e);
        E[e++] = Edge(a - 1, b - 1);
    }
}

int main() {
    Read();
    TopoSort();
    fflush(stdout);
    for(int i = 0; i < n; i++) {
        int x = topoOrder[i];
        for(int e : graph[x]) {
            int y = E[e].b;
            int indx = indexAtTopoOrder[y];
            if(x != y)
                maxEnd[indx] = max(maxEnd[indx], maxEnd[i] + 1);
        }
    }
    maxPref[0] = maxEnd[0];
    for(int i = 1; i < n; i++)
        maxPref[i] = max(maxPref[i - 1], maxEnd[i]);
    
    for(int i = n - 1; i >= 0; i--) {
        int x = topoOrder[i];
        for(int e : graph[x]) {
            int y = E[e].a;
            int indx = indexAtTopoOrder[y];
            if(x != y)
                maxBeg[indx] = max(maxBeg[indx], maxBeg[i] + 1);
        }
    }
    maxSuf[n - 1] = maxBeg[n - 1];
    for(int i = n - 2; i >= 0; i--)
        maxSuf[i] = max(maxSuf[i + 1], maxBeg[i]);
    
    Tree T(n);
    for(int i = 0; i < m; i++) {
        int a = indexAtTopoOrder[E[i].a];
        int b = indexAtTopoOrder[E[i].b];
        if(a > b)
            swap(a, b);
        if(a + 1 != b) {
            int value = maxEnd[a] + maxBeg[b] + 1;
            T.insert(a + 1, b - 1, value);
        }
    }
    
    for(int i = 0; i < n; i++) {
        int indx = indexAtTopoOrder[i];
        result[i] = T.get(indx);
        if(indx != 0)
            result[i] = max(result[i], maxPref[indx - 1]);
        if(indx != n - 1)
            result[i] = max(result[i], maxSuf[indx + 1]);
    }
    
    int lo = n, loIndx = 0;
    for(int i = 0; i < n; i++) {
        if(result[i] < lo) {
            lo = result[i];
            loIndx = i;
        }
    }
    
    printf("%d %d\n", loIndx + 1, lo);
    
    return 0;
}
