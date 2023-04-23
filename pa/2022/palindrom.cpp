#include <cstdio>
#include <vector>
#include <set>
#include <cstring>

using namespace std;

struct seg_tree {
    vector<int>v;
    int leaf_count;
    seg_tree(int n, int f) {
        for(leaf_count = 1; leaf_count < n; leaf_count *= 2) {}
        v.resize(leaf_count * 2, f);
        for(int i = leaf_count - 1; i > 0; i--)
            v[i] = v[i * 2] + v[i * 2 + 1];
    }
    void add(int x, int value) {
        for(x += leaf_count; x > 0; x /= 2)
            v[x] += value;
    }
    int sum(int a, int b) {
        if(a > b)
            return 0;
        a += leaf_count;
        b += leaf_count;
        int result = v[a];
        if(a != b)
            result += v[b];
        while(a / 2 != b / 2) {
            if(a % 2 == 0)
                result += v[a + 1];
            if(b % 2 == 1)
                result += v[b - 1];
            a /= 2;
            b /= 2;
        }
        return result;
    }
};

const int inf = 1 << 30;
const int MAX_N = 200'007;
char c[MAX_N];

int main() {
    scanf("%s", c);
    int n = strlen(c);
    vector<set<int>>s(2);
    for(int i = 0; i < n; i++)
        s[c[i] - 'a'].insert(i);
    
    if(n % 2 == 0 && s[0].size() % 2 == 1) {
        printf("-1\n");
        return 0;
    }
    
    long long result = 0;
    seg_tree t(n, 1);
    for(int i = 0; i < n / 2; i++) {
        vector<int>opt(2, inf);
        for(int j = 0; j < 2; j++) {
            if(s[j].size() >= 2) {
                auto l = *s[j].begin();
                auto r = *--s[j].end();
                int L = t.sum(0, l - 1);
                int R = t.sum(r + 1, n - 1);
                opt[j] = L + R;
            }
        }
        int j = opt[0] <= opt[1] ? 0 : 1;
        
        result += opt[j];
        int l = *s[j].begin();
        int r = *--s[j].end();
        t.add(l, -1);
        t.add(r, -1);
        s[j].erase(s[j].find(l));
        s[j].erase(s[j].find(r));
    }
    printf("%lld\n", result);
    return 0;
}
