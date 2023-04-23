#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <cmath>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<int>plus, minus;
    int zero_count = 0;
    for(int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        if(x == 0) {
            zero_count++;
        } else if(x > 0) {
            plus.push_back(x);
        } else {
            minus.push_back(x);
        }
    }
    
    if(plus.size() >= 3 || minus.size() >= 3) {
        printf("NO\n");
        return;
    }
    
    vector<int>a;
    for(int x : plus)
        a.push_back(x);
    for(int x : minus)
        a.push_back(x);
    for(int i = 0; i < min(zero_count, 3); i++)
        a.push_back(0);
    
    n = a.size();
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            for(int k = j + 1; k < n; k++) {
                
                bool ok = false;
                for(int t = 0; t < n; t++)
                    if(a[t] == a[i] + a[j] + a[k])
                        ok = true;
                    
                if(!ok) {
                    printf("NO\n");
                    return;
                }
            }
        }
    }
    printf("YES\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
