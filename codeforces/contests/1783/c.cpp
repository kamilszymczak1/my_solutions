#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    int m; scanf("%d", &m);
    
    vector<int>a(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    
    vector<pair<int, int>>a_sorted;
    for(int i = 0; i < n; i++)
        a_sorted.emplace_back(a[i], i);
    sort(a_sorted.begin(), a_sorted.end());
    vector<int>a_sorted_pref(n);
    a_sorted_pref[0] = a_sorted[0].first;
    for(int i = 1; i < n; i++)
        a_sorted_pref[i] += a_sorted_pref[i - 1] + a_sorted[i].first;
    vector<int>where(n);
    for(int i = 0; i < n; i++)
        where[a_sorted[i].second] = i;
    
    int answer = n + 1;
    for(int my_wins = 1; my_wins <= n; my_wins++) {
        if(a_sorted_pref[my_wins - 1] <= m) {
            answer = min(answer, n - my_wins + 1);
        }
        
        if(my_wins < n && where[my_wins] > my_wins - 1) {
            
            if(a[my_wins] + (my_wins == 1 ? 0 : a_sorted_pref[my_wins - 2]) <= m) {
                answer = min(answer, n - my_wins);
            }
        } else if(my_wins < n) {
            if(a_sorted_pref[my_wins - 1] <= m) {
                answer = min(answer, n - my_wins);
            }
        }
    }
    
    printf("%d\n", answer);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
