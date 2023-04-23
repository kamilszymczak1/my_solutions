#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <bitset>
#include <queue>

using namespace std;

struct dsu {
    vector<int>f;
    dsu(int n) {
        f.resize(n);
        for(int i = 0; i < n; i++)
            f[i] = i;
    }
    int find(int x) {
        return f[x] == x ? x : f[x] = find(f[x]);
    }
    void join(int x, int y) {
        f[find(x)] = find(y);
    }
};

void test_case() {
    int n, m; scanf("%d%d", &n, &m);
    
    vector<pair<int, pair<int, int>>>e;
    for(int i = 0; i < m; i++) {
        int x, y; scanf("%d%d", &x, &y);
        x--; y--;
        e.emplace_back(i, make_pair(x, y));
    }
    
    int r = m - n + 1;
    vector<int>answer(m);
    if(r < 3) {
        dsu d(n);
        for(int i = 0; i < m; i++) {
            int x = e[i].second.first;
            int y = e[i].second.second;
            if(d.find(x) != d.find(y)) {
                d.join(x, y);
            } else {
                answer[i] = 1;
            }
        }
    } else {
        
        
        for(int i = 0; i < 20; i++) {
            vector<pair<int, int>>red;
            random_shuffle(e.begin(), e.end());
            dsu d(n);
            for(int i = 0; i < m; i++) {
                int x = e[i].second.first;
                int y = e[i].second.second;
                if(d.find(x) != d.find(y)) {
                    d.join(x, y);
                    answer[e[i].first] = 0;
                } else {
                    answer[e[i].first] = 1;
                    red.emplace_back(x, y);
                }
            }
            
            vector<int>mark(n, 0);
            int count = 0;
            for(auto [x, y] : red) {
                if(!mark[x])
                    count++;
                if(!mark[y])
                    count++;
                mark[x] = mark[y] = 1;
            }
            
            if(count > 3) {
                break;
            }
        }
        
    }
    
    for(int x : answer)
        printf("%d", x);
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}
