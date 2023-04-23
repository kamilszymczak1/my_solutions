#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

void test_case() {
    int n, m; scanf("%d%d", &n, &m);
    vector<int>a(n);
    for(int &x : a)
        scanf("%d", &x);
    
    set<int>s; //in the set I store the beginning of each carriage
    s.insert(0);
    int lo = a[0];
    for(int i = 1; i < n; i++) {
        if(a[i] < lo) {
            s.insert(i);
            lo = a[i];
        }
    }
    
    while(m--) {
        int id, val; scanf("%d%d", &id, &val); id--;
        
        auto it = s.upper_bound(id); it--;
        
        int new_value = a[id] - val;
        
        auto it_r = it;
        for(it_r++; it_r != s.end() && a[*it_r] >= new_value; ) {
            auto next = it_r; next++;
            s.erase(it_r);
            it_r = next;
        }
        
        if(*it != id && new_value < a[*it]) {
            s.insert(id);
        }
        
        a[id] = new_value;
        printf("%d ", (int)s.size());
    }
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
