#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

bool Check(int s, vector<int>&x) {
    int n = x.size();
    for(int i = 0; i < n; i++) {
        if(abs(x[i] - s) > 1)
            return false;
        s++;
    }
    return true;
}

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>x(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &x[i]);
    
    bool ans = false;
    for(int i = -1; i <= 1; i++)
        ans |= Check(x[0] + i, x);
    printf("%s\n", ans ? "YES" : "NO");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
