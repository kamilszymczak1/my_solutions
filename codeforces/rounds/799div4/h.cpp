#include <cstdio>
#include <vector>
#include <map>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    map<int, vector<int>>m;
    for(int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        m[x].push_back(i);
    }
    
    int best_cost = 0;
    int best_x = 0, best_l = 0, best_r = 0;
    
    for(auto [x, vec] : m) {
        
        int max_left = 0;
        int best_left_position = -1;
        
        for(int i = 0; i < (int)vec.size(); i++) {
            int prev = i == 0 ? -1 : vec[i - 1];
            int cost = vec[i] - prev - 1;
            
            if(max_left - cost <= 0) {
                best_left_position = vec[i];
                max_left = 0;
            } else {
                max_left -= cost;
            }
            
            max_left += 1;
            
            if(max_left >= best_cost) {
                best_x = x;
                best_l = best_left_position;
                best_r = vec[i];
                best_cost = max_left;
            }
        }
    }
    
    printf("%d %d %d\n", best_x, best_l + 1, best_r + 1);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
