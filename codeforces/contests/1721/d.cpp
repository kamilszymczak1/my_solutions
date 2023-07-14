#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <stack>
#include <bitset>
#include <cstring>
#include <cmath>
#include <queue>

using namespace std;

void test_case() {
    vector<vector<vector<int>>>s(1, vector<vector<int>>(2));
    int n; scanf("%d", &n);
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < n; j++) {
            int x; scanf("%d", &x);
            s[0][i].push_back(x);
        }
    }
    
    int answer = 0;
    
    for(int bit = 29; bit >= 0; bit--) {
        
        bool split = true;
        
        for(auto &v : s) {
            vector<int>count(2, 0);
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < (int)v[i].size(); j++) {
                    int b = (v[i][j] >> bit) & 1;
                    count[b ^ i] += 2 * i - 1;
                }
            }
            
            if(count[0] != 0 || count[1] != 0)
                split = false;
        }
        
        if(split) {
            answer |= 1 << bit;
            vector<vector<vector<int>>>new_v;
            for(auto v : s) {
                
                new_v.emplace_back(vector<vector<int>>(2));
                for(int j = 0; j < (int)v[0].size(); j++) {
                    if(((v[0][j] >> bit) & 1) == 0) {
                        new_v.back()[0].emplace_back(v[0][j]);
                    }
                    
                    if(((v[1][j] >> bit) & 1) == 1) {
                        new_v.back()[1].emplace_back(v[1][j]);
                    }
                }
                
                if(new_v.back()[0].empty())
                    new_v.pop_back();
                
                new_v.emplace_back(vector<vector<int>>(2));
                for(int j = 0; j < (int)v[0].size(); j++) {
                    if(((v[0][j] >> bit) & 1) == 1)  {
                        new_v.back()[0].emplace_back(v[0][j]);
                    }
                    
                    if(((v[1][j] >> bit) & 1) == 0) {
                        new_v.back()[1].emplace_back(v[1][j]);
                    }
                }
                
                if(new_v.back()[0].empty())
                    new_v.pop_back();
            }
            
            swap(s, new_v);
        } else {
            for(auto &v : s) {
                for(int i = 0; i < 2; i++) {
                    for(int j = 0; j < (int)v[i].size(); j++) {
                        if((v[i][j] >> bit) & 1) {
                            v[i][j] ^= 1 << bit;
                        }
                    }
                }
            }
        }
        
    }
    
    printf("%d\n", answer);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}
