#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    vector<pair<int, int>>cnt(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]); a[i]--;
        cnt[a[i]].first++;
        cnt[i].second = i;
    }
    set<int>s;
    for(int i = 0; i < n; i++)
        s.insert(i);
    vector<int>b(n, -1);
    sort(cnt.begin(), cnt.end());
    reverse(cnt.begin(), cnt.end());
    for(auto [count, value] : cnt) {
        if(count == 0)
            continue;
        
        auto it = s.begin();
        while(count > 0 && it != s.end()) {
            if(a[*it] != value) {
                b[*it] = value;
                count--;
                auto next = it;
                next++;
                s.erase(it);
                it = next;
            } else {
                it++;
            }
        }
        
        if(count != 0) {
            while(count > 0) {
                b[*s.begin()] = value;
                count--;
                s.erase(s.begin());
            }
        }
    }
    
    for(int x : b)
        printf("%d ", x + 1);
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
