#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <cstring>

using namespace std;

void TestCase() {
    int n, m; scanf("%d%d", &n, &m);
    
    vector<vector<int>>grid(n, vector<int>(m)), gridS(n, vector<int>(m));
    bool f = true;
    int a = -1, b = -1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &grid[i][j]);
            gridS[i][j] = grid[i][j];
        }
        sort(gridS[i].begin(), gridS[i].end());
        
        set<int>wrong;
        for(int j = 0; j < m; j++)
            if(grid[i][j] != gridS[i][j])
                wrong.insert(j);
            
            if(wrong.size() >= 3) {
                f = false;
            }
            
            if(wrong.size() == 2) {
                auto it = wrong.begin();
                a = *it;
                it++;
                b = *it;
                it++;
            }
            
    }
    
    if(f == false) {
        printf("-1\n");
        return;
    }
    
    if(a == -1 && b == -1) {
        
        printf("1 1\n");
        return;
    }
    
    
    for(int i = 0; i < n; i++)
        swap(grid[i][a], grid[i][b]);
    
    bool ok = true;
    for(int i = 0; i < n; i++) {
        for(int j = 1; j < m; j++) {
            if(grid[i][j - 1] > grid[i][j])
                ok = false;
        }
    }
    
    if(ok) {
        printf("%d %d\n", a + 1, b + 1);
    } else {
        printf("-1\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
