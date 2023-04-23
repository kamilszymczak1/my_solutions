#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

int D(pair<int, int>a, pair<int, int>b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

char c[1'000'007];

void test_case() {
    int n, m; scanf("%d%d", &n, &m);
    
    vector<pair<int, int>>p = { {n - 1, m - 1}, {n - 1, 0}, {0, m - 1}, {0, 0} };
    
    for(int i = 0; i < n; i++) {
        scanf("%s", c);
        for(int j = 0; j < m; j++) {
            
            
            if(c[j] == 'B') {
                for(int a = 0; a < 2; a++) {
                    for(int b = 0; b < 2; b++) {
                        int ind = 2 * a + b;
                        int my_value = (2 * a - 1) * i + (2 * b - 1) * j;
                        int cu_value = (2 * a - 1) * p[ind].first + (2 * b - 1) * p[ind].second;
                        
                        if(my_value > cu_value) {
                            p[ind] = make_pair(i, j);
                        }
                    }
                }
            }
            
            
        }
    }
    
    pair<int, int>answer = {0, 0};
    int best = n + m;
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int my_answer = 0;
            for(int k = 0; k < 4; k++)
                my_answer = max(my_answer, D(make_pair(i, j), p[k]));
            
            if(my_answer < best) {
                best = my_answer;
                answer = make_pair(i, j);
            }
        }
    }
    
    printf("%d %d\n", answer.first + 1, answer.second + 1);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
