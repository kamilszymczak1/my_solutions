#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int MAX_N = 150007;
const int leafCount = 1 << 19;
vector<int>pairAdj[MAX_N], graph[3 * leafCount], graph2[3 * leafCount];

int a[MAX_N], n, k, pointing[MAX_N], ind[MAX_N], N;
bool visited[leafCount * 3];
int scc[leafCount * 3], sccCount;
map<pair<int, int>, int>m;

void DFSorder(int x, vector<int>&order) {
    visited[x] = true;
    for(int y : graph[x]) {
        if(!visited[y]) {
            DFSorder(y, order);
        }
    }
    order.push_back(x);
}

void DFSscc(int x) {
    scc[x] = sccCount;
    visited[x] = true;
    for(int y : graph2[x]) {
        if(!visited[y]) {
            DFSscc(y);
        }
    }
}

void FindSCC() {
    fill(visited, visited + leafCount * 3, false);
    vector<int>order;
    for(int i = 1; i < leafCount * 3; i++) {
        if(!visited[i]) {
            DFSorder(i, order);
        }
    }
    fill(visited, visited + leafCount * 3, false);
    sccCount = 0;
    for(; !order.empty(); order.pop_back()) {
        int x = order.back();
        if(!visited[x]) {
            ++sccCount;
            DFSscc(x);
        }
    }
}

int neg(int x) {
    return x + (x < leafCount * 2 ? leafCount : -leafCount);
}

void Connect(int a, int b, int v) {
    graph[v].push_back(a);
    graph2[a].push_back(v);
    if(a != b) {
        graph[v].push_back(b);
        graph2[b].push_back(v);
    }
    for(; (a >> 1) != (b >> 1); a >>= 1, b >>= 1) {
        if(!(a & 1)) {
            graph[v].push_back(a + 1);
            graph2[a + 1].push_back(v);
        }
        if(b & 1) {
            graph[v].push_back(b - 1);
            graph2[b - 1].push_back(v);
        }
    }
}

bool TestCase() {
    cin >> n >> k >> a[0];
    int pairCount = 0;
    N = n - 1;
    for(int i = 1; i < n; i++) {
        cin >> a[i];
        if(m[make_pair(a[i], a[i - 1])] == 0) {
            m[make_pair(a[i], a[i - 1])] = ++pairCount;
        }
        pointing[i - 1] = m[make_pair(a[i], a[i - 1])];
        pairAdj[pointing[i - 1]].push_back(i - 1);
    }
    
    
    
    for(int i = 1, currentIndex = leafCount; i <= pairCount; i++) {
        for(int x : pairAdj[i]) {
            ind[x] = currentIndex++;
        }
        
        int l = ind[pairAdj[i][0]], r = ind[pairAdj[i].back()];
        for(int x : pairAdj[i]) {
            if(ind[x] != l) {
                Connect(l, ind[x] - 1, neg(ind[x]));
            }
            if(ind[x] != r) {
                Connect(ind[x] + 1, r, neg(ind[x]));
            }
        }
    }
    
    for(int i = 1; i < leafCount; i++) {
        graph[i].push_back(i * 2);
        graph[i].push_back(i * 2 + 1);
        graph2[i * 2].push_back(i);
        graph2[i * 2 + 1].push_back(i);
    }
    
    
    graph[neg(ind[0])].push_back(neg(ind[N - 1]));
    graph[neg(ind[N - 1])].push_back(neg(ind[0]));
    graph2[neg(ind[0])].push_back(neg(ind[N - 1]));
    graph2[neg(ind[N - 1])].push_back(neg(ind[0]));
    
    graph[ind[0]].push_back(neg(ind[N - 1]));
    graph[ind[N - 1]].push_back(neg(ind[0]));
    graph2[neg(ind[N - 1])].push_back(ind[0]);
    graph2[neg(ind[0])].push_back(ind[N - 1]);
    
    for(int i = 0; i < N; i++) {
        if(i != 0) {
            graph[ind[i]].push_back(neg(ind[i - 1]));
            graph2[neg(ind[i - 1])].push_back(ind[i]);
        }
        if(i != N - 1) {
            graph[ind[i]].push_back(neg(ind[i + 1]));
            graph2[neg(ind[i + 1])].push_back(ind[i]);
        }
    }
    
    
    FindSCC();
    
    bool result = true;
    for(int i = 0; i < N; i++)
        if(scc[ind[i]] == scc[neg(ind[i])])
            result = false;
        
    for(int i = 1; i <= 3 * leafCount; i++) {
        graph[i].clear();
        graph2[i].clear();
    }
    for(int i = 1; i <= pairCount; i++)
        pairAdj[i].clear();
    m.clear();
    return result || n == 2;
}

int main() {
    ios_base::sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--) {
        if(TestCase()) {
            cout << "TAK\n";
        } else {
            cout << "NIE\n";
        }
    }
    
    return 0;
}
