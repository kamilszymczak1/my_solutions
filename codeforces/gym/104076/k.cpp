#include <cstdio>
#include <set>
    
using namespace std;
    
void test_case() {
    int n; scanf("%d", &n);
    set<int>s;
    for(int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        auto it = s.lower_bound(x);
        if(s.find(x + 1) != s.end()) {
            s.erase(s.find(x + 1));
        }
        s.insert(x);
    }
    printf("%d\n", (int)s.size());
}
    
int main() {
    int t; scanf("%d", &t);
    while(t--) {
        test_case();
    }
    return 0;
}
