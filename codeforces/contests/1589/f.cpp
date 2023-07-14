#include <cstdio>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

int char_id[1 << 8], mapped_char[1 << 8];
const int A = 52;
char c[200];

void get_order(int x, vector<vector<int>>&out, vector<bool>&visited, vector<int>&order) {
    visited[x] = true;
    for(int y : out[x]) {
        if(!visited[y]) {
            get_order(y, out, visited, order);
        }
    }
    order.push_back(x);
}

void test_case() {
    int n; scanf("%d", &n);
    vector<vector<vector<int>>>pos(n, vector<vector<int>>(A));
    
    for(int i = 0; i < n; i++) {
        scanf("%s", c);
        for(int j = 0; c[j] != 0; j++) {
            pos[i][char_id[c[j]]].push_back(j);
        }
    }
    
    int nodes = A * (1 << n);
    
    vector<vector<int>>out(nodes);
    vector<int>dp(nodes);
    
    for(int my_char = 0; my_char < A; my_char++) {
        
        for(int i = 0; i < (1 << n); i++) {
            
            bool valid = true;
            for(int j = 0; j < n; j++) {
                if(pos[j][my_char].size() <= ((i >> j) & 1)) {
                    valid = false;
                    break;
                }
            }
            
            if(!valid)
                continue;
            
            dp[my_char * (1 << n) + i] = 1;
            
            
            for(int other_char = 0; other_char < A; other_char++) {
                valid = true;
                int other_mask = 0;
                for(int j = 0; j < n; j++) {
                    int my_pos = pos[j][my_char][(i >> j) & 1];
                    
                    int k = 0;
                    while(k < (int)pos[j][other_char].size() && pos[j][other_char][k] <= my_pos)
                        k++;
                    
                    if(k == (int)pos[j][other_char].size()) {
                        valid = false;
                        break;
                    }
                    
                    other_mask |= k << j;
                }
                
                if(valid) {
                    out[my_char * (1 << n) + i].push_back(other_char * (1 << n) + other_mask);
                }
            }
        }
    }
    
    vector<bool>visited(nodes, false);
    vector<int>order, parent(nodes, -1);
    for(int i = 0; i < nodes; i++) {
        if(!visited[i]) {
            get_order(i, out, visited, order);
        }
    }
    
    int hi = 0;
    for(int x : order) { 
        for(int y : out[x]) {
            if(dp[y] + 1 > dp[x]) {
                parent[x] = y;
                dp[x] = dp[y] + 1;
            }
        }
        if(dp[x] >= dp[hi]) {
            hi = x;
        }
    }
    
    int answer = dp[hi];
    for(int i = 0; i < answer; i++) {
        c[i] = mapped_char[hi >> n];
        hi = parent[hi];
    }
    c[answer] = 0;
    printf("%d\n%s\n", answer, c);
}

int main() {
    for(int i = 'a'; i <= 'z'; i++) {
        char_id[i] = i - 'a';
        mapped_char[i - 'a'] = i;
    }
    
    for(int i = 'A'; i <= 'Z'; i++) {
        char_id[i] = i - 'A' + 26;
        mapped_char[i - 'A' + 26] = i;
    }
    
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
