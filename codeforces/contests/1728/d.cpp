#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

char c[2007];

const int A = 1, B = -1, D = 0;

void test_case() {
    scanf("%s", c);
    int n = strlen(c);
    
    vector<int>who_wins(n - 1);
    for(int i = 0; i < n - 1; i++) {
        if(c[i] == c[i + 1]) {
            who_wins[i] = D;
        } else {
            who_wins[i] = A;
        }
    }
    
    for(int len = 4; len <= n; len += 2) {
        vector<int>new_wins(n - len + 1);
        
        for(int i = 0; i < n - len + 1; i++) {
            
            int best = B;
            
            int x = i, y = i + len - 1;
            
            vector<int>a_choice = {x, y};
            vector<vector<int>>b_choice = {{x + 1, y}, {x, y - 1}};
            
            
            vector<vector<int>>ind = {{i + 2, i + 1}, {i + 1, i}};
            
            int a_best = B;
            
            for(int k = 0; k < 2; k++) {
                
                int a_c = a_choice[k];
                int b_best = A;
                for(int t = 0; t < 2; t++) {
                    int b_c = b_choice[k][t];
                    
                    int index = ind[k][t];
                    
                    if(who_wins[index] == D) {
                        if(c[a_c] == c[b_c]) {
                            b_best = min(b_best, D);
                        } else {
                            b_best = min(b_best, c[a_c] < c[b_c] ? A : B);
                        }
                    } else if(who_wins[index] == B) {
                        b_best = min(b_best, B);
                    }
                }
                
                a_best = max(a_best, b_best);
            }
            
            new_wins[i] = a_best;
        }
        
        swap(new_wins, who_wins);
    }
    
    if(who_wins[0] == A) {
        printf("Alice\n");
    } else if(who_wins[0] == B) {
        printf("Bob\n");
    } else {
        printf("Draw\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}

