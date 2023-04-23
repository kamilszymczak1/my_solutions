#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>a(n), b(n);
    vector<bool>skipped(n, false);
    vector<vector<int>>pos(n + 1);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        pos[a[i]].push_back(i);
    }
        
    for(int i = 0; i < n; i++)
        scanf("%d", &b[i]);
    
    int j = n - 1;
   // vector<bool>ok(n + 1, false);
    for(int i = n - 1; i >= 0; i--) {
        while(j >= 0 && skipped[j] && a[j] != b[i]) {
            j--;
        }
        if(j < 0 || a[j] != b[i]) {
            printf("NO\n");
            return;
        }
        //ok[b[i]] = false;
        int k = i;
        while(k >= 0 && b[k] == b[i])
            k--;
        for(int t = 0; t < i - k; t++) {
            skipped[pos[b[i]].back()] = true;
            pos[b[i]].pop_back();
        }
        
        i = k + 1;
    }
    printf("YES\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
