#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct DynamicMex {
    set<int>complement;
    map<int, int>cnt;
    int size;
    int __cnt;
    DynamicMex(int _size) {
        for(int i = 0; i <= _size; i++)
            complement.insert(i);
        __cnt = 0;
    }
    void Add(int x) {
        cnt[x]++;
        if(cnt[x] == 1)
            complement.erase(complement.find(x));
        __cnt++;
    }
    void Erase(int x) {
        cnt[x]--;
        if(cnt[x] == 0)
            complement.insert(x);
        __cnt++;
    }
    int GetMex() {
        return *complement.begin();
    }
};

int Find(int x, vector<int>&f) {
    return f[x] == x ? x : f[x] = Find(f[x], f);
}

void AUnion(int x, int y, vector<int>&f, vector<set<int>>&a, DynamicMex &mex, vector<bool>&containsZero) {
    x = Find(x, f);
    y = Find(y, f);
    if(a[x].size() < a[y].size())
        swap(x, y);
    if(containsZero[x]) {
        for(int z : a[y]) {
            mex.Add(z);
        }
        
    } else if(containsZero[y]) {
        for(int z : a[x]) {
            mex.Add(z);
        }
        
    }
    
    for(int z : a[y])
        a[x].insert(z);
    a[y].clear();
    f[y] = x;
    containsZero[x] = containsZero[y] | containsZero[x];
}

void BUnion(int x, int y, vector<int>&f, vector<set<int>>&a, DynamicMex &mex, vector<bool>&visited, bool mexInsert) {
    x = Find(x, f);
    y = Find(y, f);
    if(mexInsert) {
        for(int z : a[y]) {
            mex.Add(z);
        } 
    }
    
    if(visited[x]) {
        for(int z : a[y]) {
            mex.Erase(z);
        }
    }
    
    if(visited[y]) {
        for(int z : a[x]) {
            mex.Erase(z);
        }
    }
    
    if(a[x].size() < a[y].size()) {
        swap(x, y);
    }
    
    for(int z : a[y])
        a[x].insert(z);
    a[y].clear();
    visited[x] = visited[y] | visited[x];
    f[y] = x;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, m1, m2; cin >> n >> m1 >> m2;
    vector<pair<int, int>>aEdges(m1), bEdges(m2);
    vector<set<int>>a(n), b(n);
    vector<int>af(n), bf(n);
    vector<bool>containsZero(n, false), bVisited(n, false);
    DynamicMex mex(n + 1);
    
    for(auto &[x, y] : aEdges) {
        cin >> x >> y;
        x--; y--;
    }
    
    for(auto &[x, y] : bEdges) {
        cin >> x >> y;
        x--; y--;
    }
    
    if(m1 < m2) {
        swap(aEdges, bEdges);
        swap(m1, m2);
    }
    
    for(int i = 0; i < n; i++) {
        a[i].insert(i);
        b[i].insert(i);
        af[i] = bf[i] = i;
    }
    containsZero[0] = true;
    
    for(auto &[x, y] : aEdges) {
        AUnion(x, y, af, a, mex, containsZero);
    }
    
    for(auto &[x, y] : bEdges) {
        BUnion(x, y, bf, b, mex, bVisited, false);
    }
    
    
    cout << n - m1 - 1 << '\n';
    
    mex.Add(0);
    
    int delCnt = 0;
    
    int edges = m1;
    while(edges < n - 1) {
        int x = Find(0, af);
        int node = *a[x].begin();
        
        int y = Find(node, bf);
        
        if(!bVisited[y]) {
            for(int z : b[y]) {
                mex.Add(z);
            }
            bool toDelete = true;
            while(mex.GetMex() < n && !bVisited[y]) {
                edges++;
                cout << node + 1 << ' ' << mex.GetMex() + 1 << '\n' << flush;
                int k = mex.GetMex();
                AUnion(node, k, af, a, mex, containsZero);
                if(bVisited[Find(k, bf)] || bVisited[Find(node, bf)]) {
                    BUnion(node, k, bf, b, mex, bVisited, false);
                    toDelete = false;
                    break;
                } else {
                    BUnion(node, k, bf, b, mex, bVisited, true);
                }
                y = Find(y, bf);
            }
            y = Find(node, bf);
            bVisited[y] = true;
            if(toDelete) {
                for(int z : b[y]) {
                    delCnt++;
                    mex.Erase(z);
                }
            }
        }
        x = Find(0, af);
        a[x].erase(a[x].find(node));
    }
    
    return 0;
}
