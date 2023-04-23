#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <map>

using namespace std;

constexpr int inf = 999999999;

pair<int, int> operator+(pair<int, int>a, pair<int, int>b) {
    return make_pair(a.first + b.first, a.second + b.second);
}

pair<int, int> operator*(pair<int, int>a, int b) {
    return make_pair(a.first * b, a.second * b);
}

struct DSU {
    vector<int>f;
    DSU(int _n) {
        f.resize(_n);
        iota(f.begin(), f.end(), 0);
    }
    int Find(int x) {
        return f[x] == x ? x : f[x] = Find(f[x]);
    }
    void Union(int x, int y) {
        f[Find(x)] = Find(y);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    int n, k, q; cin >> n >> k >> q;
    string pattern; cin >> pattern;
    
    vector<pair<int, int>>obstacles;
    for(int i = 0; i < k; i++) {
        int x, y; cin >> x >> y;
        obstacles.emplace_back(x, y);
    }
    
    map<pair<int, int>, int>robots;
    
    DSU dsu(q);
    
    for(int i = 1; i <= q; i++) {
        int x, y; cin >> x >> y;
        if(robots[{x, y}] != 0) {
            dsu.Union(i - 1, robots[{x, y}] - 1);
        } else {
            robots[{x, y}] = i;
        }
    }
    
    map<char, pair<int, int>>moves;
    moves['U'] = make_pair(0, -1);
    moves['D'] = make_pair(0, 1);
    moves['L'] = make_pair(1, 0);
    moves['R'] = make_pair(-1, 0);
    
    
    pair<int, int>totalOffset = make_pair(0, 0);
    for(char c : pattern) {
        const pair<int, int>move = moves[c];
        totalOffset = totalOffset + move * (-1);
        
        for(pair<int, int>&obstacle : obstacles) {
            pair<int, int>closer = obstacle + move, further = obstacle + move * 2;
            if(robots[closer] != 0) {
                if(robots[further] != 0) {
                    dsu.Union(robots[closer] - 1, robots[further] - 1);
                } else {
                    robots[further] = robots[closer];
                } 
            }
            robots.erase(closer);
            obstacle = obstacle + move;
        }
    }
    
    vector<pair<int, int>>ans(q);
    for(pair<pair<int, int>, int>p : robots) {
        ans[p.second - 1] = p.first + totalOffset;
    }
    for(int i = 0; i < q; i++)
        ans[i] = ans[dsu.Find(i)];
    for(const pair<int, int>p : ans)
        cout << p.first << ' ' << p.second << '\n';
    
    return 0;
}

/*
4 2 5
LURD
0 0
1 2
1 0
1 1
2 0
2 1
2 2
*/
