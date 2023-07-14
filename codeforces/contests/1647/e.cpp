#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int Jump(int v, int t, vector<vector<int>>&jump) {
    for(int i = (int)jump[v].size() - 1; i >= 0; i--) {
        if((1 << i) <= t) {
            v = jump[v][i];
            t -= 1 << i;
        }
    }
    return v;
}

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>p(n), a(n), indeg(n);
    vector<bool>stillInClass(n, false);
    for(int i = 0; i < n; i++) {
        scanf("%d", &p[i]); p[i]--;
        indeg[p[i]]++;
    }
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]); a[i]--;
        if(a[i] < n)
            stillInClass[a[i]] = true;
    }
    
    int k = 0;
    for(int i = 0; i < n; i++)
        k += indeg[i] == 0;
    
    int t = (*max_element(a.begin(), a.end()) - n + 1) / k;
    
    vector<vector<int>>jump(n);
    for(int i = 0; i < n; i++)
        jump[i].push_back(p[i]);
    for(int i = 1; i < 30; i++) {
        for(int v = 0; v < n; v++) {
            jump[v].push_back(jump[jump[v][i - 1]][i - 1]);
        }
    }
    vector<set<int>>positionsTo(n);
    set<int>others;
    for(int i = 0; i < n; i++) {
        if(!stillInClass[i])
            others.insert(i);
        int j = Jump(i, t, jump);
        positionsTo[j].insert(i);
    }
    vector<int>b(n, -1);
    for(int i = 0; i < n; i++) {
        if(a[i] < n) {
            b[*positionsTo[i].begin()] = a[i];
        }
    }
    for(int i = 0; i < n; i++) {
        if(b[i] == -1) {
            int j = Jump(i, t, jump);
            b[i] = *others.lower_bound(b[*positionsTo[j].begin()]);
            others.erase(others.find(b[i]));
        }
    }
    for(int i = 0; i < n; i++)
        printf("%d ", b[i] + 1);
    printf("\n");
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
