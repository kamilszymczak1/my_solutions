#include <cstdio>
#include <algorithm>
#include <vector>
#include <bitset>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <bitset>
#include <cmath>
#include <cassert>

using namespace std;

const int inf = 1 << 30;

struct SegmentTree {
    vector<pair<int, int>>values_mx, values_mn;
    int leaf_count;
    SegmentTree(vector<int>a) {
        int n = a.size();
        for(leaf_count = 1; leaf_count < n; leaf_count *= 2) {}
        values_mx.resize(leaf_count * 2);
        values_mn.resize(leaf_count * 2);
        for(int i = 0; i < leaf_count; i++) {
            values_mx[i + leaf_count].second = i;
            values_mn[i + leaf_count].second = i;
        }
            
        
        for(int i = 0; i < n; i++) {
            values_mx[i + leaf_count].first = a[i];
            values_mn[i + leaf_count].first = a[i];
        }
        for(int i = n; i < leaf_count; i++) {
            values_mx[i + leaf_count].first = -inf;
            values_mn[i + leaf_count].first = inf;
        }
        
        for(int i = leaf_count - 1; i > 0; i--) {
            values_mx[i] = max(values_mx[i * 2], values_mx[i * 2 + 1]);
            values_mn[i] = min(values_mn[i * 2], values_mn[i * 2 + 1]);
        }
    }
    
    pair<pair<int, int>, pair<int, int>> get_max_min(int a, int b) {
        assert(a <= b);
        a += leaf_count;
        b += leaf_count;
        auto answer = make_pair(max(values_mx[a], values_mx[b]), min(values_mn[a], values_mn[b]));
        for(; a / 2 != b / 2; a /= 2, b /= 2) {
            if(a % 2 == 0) {
                answer.first = max(answer.first, values_mx[a + 1]);
                answer.second = min(answer.second, values_mn[a + 1]);
            }
            if(b % 2 == 1) {
                answer.first = max(answer.first, values_mx[b - 1]);
                answer.second = min(answer.second, values_mn[b - 1]);
            }
        }
        return answer;
    }
};

int get(int l, int r, SegmentTree &T) {
    if(l == r)
        return 0;
    auto mx_mn = T.get_max_min(l, r);
    
    int max_index = mx_mn.first.second;
    int min_index = mx_mn.second.second;
    
    if(max_index == l && min_index == r) {
        return 1;
    }
    
    if(max_index == r && min_index == l) {
        return 1;
    }
    
    if(max_index == r || max_index == l)
        return get(l, min_index, T) + get(min_index, r, T);
    return get(l, max_index, T) + get(max_index, r, T);
}

void test_case() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int &x : a)
        scanf("%d", &x);
    SegmentTree T(a);
    
    printf("%d\n", get(0, n - 1, T));
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
