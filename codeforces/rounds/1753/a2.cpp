#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <set>
#include <queue>
#include <map>
#include <stack>
#include <cmath>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    set<pair<int, int>>s;
    vector<int>a(n);
    int total_sum = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        total_sum += a[i];
    }
    if(abs(total_sum) % 2 != 0) {
        printf("-1\n");
        return;
    }
    
    vector<pair<int, int>>seg;
    for(int i = 0; i < n; i++) {
        int j = i + 1;
        while(j < n - 1 && a[j] == 0) {
            j++;
        }
        
        if(a[i] == 0) {
            seg.emplace_back(i + 1, j);
            i = j - 1;
            continue;
        }
        
        if(j == i + 1) {
            if(a[i] == a[j]) {
                seg.emplace_back(i + 1, i + 2);
            } else {
                seg.emplace_back(i + 1, i + 1);
                seg.emplace_back(i + 2, i + 2);
            }
        } else {
            int zero_count = j - i + 1 - 2;
            if(a[i] == a[j]) {
                if(zero_count % 2 == 1) {
                    seg.emplace_back(i + 1, i + 1);
                    seg.emplace_back(i + 2, j + 1);
                } else {
                    seg.emplace_back(i + 1, i + 2);
                    seg.emplace_back(i + 3, j + 1);
                }
            } else {
                if(zero_count % 2 == 1) {
                    seg.emplace_back(i + 1, j + 1);
                } else {
                    seg.emplace_back(i + 1, i + 1);
                    seg.emplace_back(i + 2, j + 1);
                }
            }
        }
        
        i = j;
    }
    
    printf("%d\n", (int)seg.size());
    for(auto [a, b] : seg)
        printf("%d %d\n", a, b);
    
    
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
