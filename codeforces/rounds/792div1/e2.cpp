#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <cstring>

using namespace std;

void TestCase() {
    int n, k; scanf("%d%d", &n, &k);
    map<int, int>m;
    for(int i = 0; i < n; i++) {
        int a; scanf("%d", &a);
        m[a]++;
    }
    vector<pair<int, int>>v;
    for(auto &[a, b] : m)
        v.emplace_back(b, a);
    
    sort(v.begin(), v.end());
    
    map<int, int>pos;
    for(int i = 0; i < (int)v.size(); i++)
        pos[v[i].second] = i;
    
    //I want to eliminate diff
    int result = 2 * n;
    int currentMoves = 0, skipped = 0;
    int t = 0, gaps = 0;
    
    for(int mex = 0; mex <= n; mex++) {
        while(t < (int)v.size() && v[t].first + currentMoves <= k) {
            currentMoves += v[t].first;
            skipped += 1;
            t++;
        }
        
//         printf("mex = %d\n", mex);
//         printf("currentMoves = %d\n", currentMoves);
//         printf("skipped = %d\n", skipped);
        
        if(currentMoves <= k && k >= gaps) {
            //printf("ans = %d\n", (int)v.size() - skipped - mex + gaps);
            result = min(result, (int)v.size() - skipped - mex + gaps);
        }
        
        //I want to place mex to the left
        if(m[mex] != 0) {
            int p = pos[mex];
            if(p < t) {
                currentMoves -= m[mex];
                skipped -= 1;
            }
                
        } else {
            gaps++;
        }
    }
    
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
