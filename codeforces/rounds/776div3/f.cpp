#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const long long inf = 1ll << 60;

struct Option {
    int e, t, p, id;
    Option(int _e, int _t, int _p, int _id) : e(_e), t(_t), p(_p), id(_id) {}
};

bool operator< (Option &a, Option &b) {
    return a.e < b.e;
}

void TestCase() {
    int n, m; scanf("%d%d", &n, &m);
    vector<int>a(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    vector<Option>o;
    for(int i = 0; i < m; i++) {
        int e, t, p; scanf("%d%d%d", &e, &t, &p);
        o.emplace_back(e - 1, t, p, i);
    }
    sort(o.begin(), o.end());
    int time = 0, j = 0;
    vector<int>ans;
    for(int i = 0; i < n; i++) {
        vector<vector<int>>parent(200);
        vector<long long>k(200, inf);
        k[0] = 0;
        while(j < m && o[j].e == i) {
            for(int t = 200 - o[j].p - 1; t >= 0; t--) {
                if(k[t + o[j].p] > k[t] + o[j].t) {
                    k[t + o[j].p] = k[t] + o[j].t;
                    parent[t + o[j].p] = parent[t];
                    parent[t + o[j].p].push_back(o[j].id);
                }
            }
            j++;
        }
        int best = 100;
        for(int j = 101; j < 200; j++) {
            if(k[j] < k[best]) {
                best = j;
            }
        }
        if(time + k[best] > a[i]) {
            printf("-1\n");
            return;
        }
        time += k[best];
        for(int z : parent[best])
            ans.push_back(z + 1);
    }
    printf("%d\n", (int)ans.size());
    for(int x : ans)
        printf("%d ", x);
    putchar('\n');
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    
    return 0;
}
