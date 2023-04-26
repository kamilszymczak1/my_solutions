#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <cmath>
#include <cstring>

using namespace std;

int next_int() {
    int x; scanf("%d", &x);
    if(x == -1)
        exit(0);
    return x;
}

int query(int x, int y) {
    printf("? %d %d\n", x, y);
    fflush(stdout);
    return next_int();
}

void test_case() {
    int n = next_int();
    vector<int>v(1 << n);
    for(int i = 1; i <= (1 << n); i++)
        v[i - 1] = i;
    
    while(v.size() >= 4) {
        vector<int>new_v(v.size() / 4);
        for(int i = 0; i < (int)v.size() / 4; i++) {
            int a = v[i * 4 + 0], b = v[i * 4 + 1];
            int c = v[i * 4 + 2], d = v[i * 4 + 3];
            
            int t = query(a, d);
            if(t == 0) {
                new_v[i] = query(b, c) == 1 ? b : c;
            } else if(t == 1) {
                new_v[i] = query(a, c) == 1 ? a : c;
            } else {
                new_v[i] = query(b, d) == 1 ? b : d;
            }
        }
        swap(v, new_v);
    }
    
    if(v.size() == 2) {
        printf("! %d\n", query(v[0], v[1]) == 1 ? v[0] : v[1]);
    } else {
        printf("! %d\n", v[0]);
    }
    fflush(stdout);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
