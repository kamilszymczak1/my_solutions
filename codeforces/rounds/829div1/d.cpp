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

const int MAX_N = 300'007;

const long long inf = 1ll << 60;

char c[MAX_N];

void test_case() {
    int n, m; scanf("%d%d", &n, &m);
    vector<vector<bool>>blocked(n, vector<bool>(m, false));
    vector<vector<long long>>d(n, vector<long long>(m, inf));
    
    long long p, q; scanf("%lld%lld", &p, &q);
    
    set<pair<long long, pair<int, int>>>s;
    for(int i = 0; i < n; i++) {
        scanf("%s", c);
        for(int j = 0; j < m; j++){ 
            if(c[j] == '#') {
                blocked[i][j] = true;
            } else {
                if(c[j] == '.') {
                    d[i][j] = 0;
                }
                s.insert(make_pair(d[i][j], make_pair(i, j)));
            }
            
        }
    }
    
    while(!s.empty()) {
        auto [my_d, P] = *s.begin();
        s.erase(s.begin());
        int x = P.first, y = P.second;
        
        static int moves_a[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        static int moves_b[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
        
        vector<bool>valid(4, false);
        for(int i = 0; i < 4; i++) {
            int X = x + moves_a[i][0];
            int Y = y + moves_a[i][1];
            valid[i] = X >= 0 && X < n && Y >= 0 && Y < m && !blocked[X][Y];
        }
        for(int i = 0; i < 4; i++) {
            int X = x + moves_b[i][0];
            int Y = y + moves_b[i][1];
            if(X >= 0 && X < n && Y >= 0 && Y < m && !blocked[X][Y]) {
                if(valid[i] || valid[(i + 1) % 4]) {
                    
                    if(d[X][Y] > d[x][y] + p) {
                        s.erase(s.find(make_pair(d[X][Y], make_pair(X, Y))));
                        d[X][Y] = d[x][y] + p;
                        s.insert(make_pair(d[X][Y], make_pair(X, Y)));
                    }
                }
            }
        }
        
        for(int i = 0; i < 4; i++) {
            int X = x + moves_a[i][0] * 2;
            int Y = y + moves_a[i][1] * 2;
            if(X >= 0 && X < n && Y >= 0 && Y < m && !blocked[X][Y] && valid[i]) {
                if(d[X][Y] > d[x][y] + q) {
                    s.erase(s.find(make_pair(d[X][Y], make_pair(X, Y))));
                    d[X][Y] = d[x][y] + q;
                    s.insert(make_pair(d[X][Y], make_pair(X, Y)));
                }
            }
        }
    }
    
    long long answer = inf;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(blocked[i][j])
                continue;
            static int moves_a[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            for(int k = 0; k < 4; k++) {
                int x = i + moves_a[k][0];
                int y = j + moves_a[k][1];
                if(x >= 0 && x < n && y >= 0 && y < m && !blocked[x][y]) {
                    answer = min(answer, d[i][j] + d[x][y]);
                }
            }
        }
    }
    
    if(answer == inf) {
        printf("-1\n");
    } else {
        printf("%lld\n", answer);
    }
}

int main() {
    int t = 1;
    while(t--)
        test_case();
    return 0;
}
