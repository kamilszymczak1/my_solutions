#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <cstring>

using namespace std;

struct SegTree {
    vector<int>values;
    int leafCount;
    SegTree(int n) {
        for(leafCount = 1; leafCount < n; leafCount *= 2) {}
        values.resize(leafCount * 2);
    }
    void Add(int x, int value) {
        for(x += leafCount; x > 0; x /= 2)
            values[x] += value;
    }
    void Set(int x, int value) {
        x += leafCount;
        values[x] = value;
        for(x /= 2; x; x /= 2)
            values[x] = values[x * 2] + values[x * 2 + 1];
    }
    int Bound(int s) {
        if(s >= values[1])
            return leafCount;
        return BoundRec(1, s);
    }
    int BoundRec(int v, int s) {
        if(v >= leafCount)
            return v - leafCount;
        
        if(values[v * 2] <= s)
            return BoundRec(v * 2 + 1, s - values[v * 2]);
        return BoundRec(v * 2, s);
    }
    int Sum(int a, int b) {
        a += leafCount; b += leafCount;
        int result = values[a];
        if(a != b)
            result += values[b];
        while(a / 2 != b / 2) {
            if(a % 2 == 0)
                result += values[a + 1];
            if(b % 2 == 1)
                result += values[b - 1];
            a /= 2;
            b /= 2;
        }
        return result;
    }
};

void TestCase() {
    int n, k; scanf("%d%d", &n, &k);
    map<int, int>m, id;
    for(int i = 0; i < n; i++) {
        int a; scanf("%d", &a);
        m[a]++;
    }
    
    vector<pair<int, int>>v;
    for(auto &[a, b] : m)
        v.emplace_back(b, a);
    
    SegTree T1(v.size()), T2(v.size());
    
    sort(v.begin(), v.end());
    for(int i = 0; i < (int)v.size(); i++) {
        T1.Add(i, v[i].first);
        id[v[i].second] = i;
    }
    
    int result = 2 * n;
    
    int gaps = 0;
    
    for(int mex = 0; mex <= n && gaps <= k; mex++) {
        
        if(m[mex] != 0) {
            T1.Set(id[mex], 0);
            T2.Add(id[mex], 1);
        }
        
        if(k >= m[mex]) {
            
            int skipped = 0;
            int movesAvailable = k - m[mex];
            if(m[mex] != 0)
                skipped++;
            
            int hi = min(T1.Bound(movesAvailable), (int)v.size());
            if(hi > 0) {
                skipped += hi - T2.Sum(0, hi - 1);
            }
            
            result = min(result, (int)v.size() - skipped - mex + gaps);
        }
        
        gaps += m[mex] == 0;
    }
    
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
