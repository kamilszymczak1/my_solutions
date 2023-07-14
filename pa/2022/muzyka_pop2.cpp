#include <cstdio>
#include <vector>
#include <set>

using namespace std;

int main() {
    
    int n; scanf("%d", &n);
    bool found = false;
    int k = 0;
    int bit_sum = 0;
    while(!found) {
        k++;
        bit_sum += __builtin_popcount(k);
        
        if(bit_sum >= n) {
            int l = bit_sum - n;
            vector<bool>bag(l + 1, false);
            vector<pair<int, int>>parent(l + 1, make_pair(-1, -1));
            bag[0] = true;
            
            for(int i = 1; i < k; i++) {
                int cnt = __builtin_popcount(i);
                for(int j = l - cnt; j >= 0; j--) {
                    if(bag[j] == true) {
                        parent[j + cnt] = make_pair(i, j);
                        bag[j + cnt] = true;
                    }
                }
            }
            
            if(bag[l] == true) {
                
                set<int>answer;
                for(int i = 1; i <= k; i++)
                    answer.insert(i);
                
                for(int i = l; i != 0; i = parent[i].second) {
                    answer.erase(answer.find(parent[i].first));
                }
                
                printf("%d\n", (int)answer.size());
                for(auto it = answer.rbegin(); it != answer.rend(); it++)
                    printf("%d ", *it);
                printf("\n");
                
                found = true;
            }
        }
        
    }
    return 0;
}
