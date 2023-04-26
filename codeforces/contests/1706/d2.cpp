#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cstring>
#include <bitset>
#include <list>

using namespace std;

struct S {
    int x, p;
    int value() { return x / p; }
    S(int _x, int _p) : x(_x), p(_p) {}
};

bool operator< (S a, S b) {
    if(a.value() == b.value())
        return a.x < b.x;
    return a.value() < b.value();
}

const int MAX_A = 100'001;
vector<pair<int, int>>v[MAX_A];

int GetP(int x, int p) {
    if(p == 1)
        return -1;
    return x / (x / p + 1);
}

void TestCase() {
    int n, k; scanf("%d%d", &n, &k);
    int mx = 0;
    for(int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        v[x / k].emplace_back(x, k);
        mx = max(mx, x / k);
    }
    int result = 1 << 29;
    bool ok = true;
    for(int i = 0; i < MAX_A && ok; i++) {
        result = min(result, mx - i);
        while(!v[i].empty() && ok) {
            auto [x, p] = v[i].back();
            v[i].pop_back();
            
            if(p == 1) {
                ok = false;
                for(int j = i; j < MAX_A; j++) {
                    while(!v[j].empty())
                        v[j].pop_back();
                    v[j].shrink_to_fit();
                }
                continue;
            }
            
            p = GetP(x, p);
            while(GetP(x, p) != -1 && x / GetP(x, p) <= mx)
                p = GetP(x, p);
            
            
            v[x / p].emplace_back(x, p);
            mx = max(mx, x / p);
        }
        v[i].shrink_to_fit();
    }
    
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    
    return 0;
}
