#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const long long mod = 998244353;

struct Edge {
    int to;
    vector<pair<int, int>>x, y;
    Edge(int _to, vector<pair<int, int>>_x, vector<pair<int, int>>_y) {
        to = _to;
        x = _x;
        y = _y;
    }
    Edge() {}
};

long long Pow(int x, int exp) {
    if(exp <= 0)
        return 1;
    long long result = Pow(x, exp / 2);
    result = (result * result) % mod;
    if(exp % 2 == 1)
        result = (result * x) % mod;
    return result;
}

long long Inv(int x) {
    return Pow(x, mod - 2);
}

void DFS(int x, int p, vector<vector<Edge>>&adj, vector<set<pair<int, int>>>&s, vector<long long>&sum, vector<long long>&A) {
    A[x] = 1;
    if(adj[x].size() == 1 && p != -1) {
        sum[x] = 1;
        return;
    }
/*    
    printf("DFS at %d\n", x + 1);*/
    for(Edge &e : adj[x]) {
        if(e.to != p) {
//             printf("son = %d\n", e.to + 1);
            DFS(e.to, x, adj, s, sum, A);
            long long mult = 1;
            for(auto [value, count] : e.x) {
//                 printf("mult by (%d %d)\n", value, count);
                auto it = s[e.to].lower_bound(make_pair(value, -1));
                if(it == s[e.to].end() || it -> first != value) {
                    s[e.to].insert(make_pair(value, count));
                    mult = mult * Pow(value, count) % mod;
                } else {
                    int count2 = it -> second;
                    if(count2 < count) {
                        s[e.to].erase(it);
                        s[e.to].insert(make_pair(value, count));
                        mult = mult * Pow(value, count - count2) % mod;
                    }
                    
                }
            }
//             printf("mult of %d: %d\n", e.to + 1, mult);
            A[e.to] = A[e.to] * mult % mod;
            sum[e.to] = sum[e.to] * mult % mod;
            
        }
    }
    
    for(Edge &e : adj[x]) {
        if(e.to != p) {
            for(auto [value, count] : e.x) {
                auto it = s[e.to].lower_bound(make_pair(value, -1));
                int count2 = it -> second;
                A[e.to] = A[e.to] * Inv(Pow(value, count)) % mod;
                s[e.to].erase(it);
                if(count2 > count) {
                    s[e.to].insert(make_pair(value, count2 - count));
                }
            }
            
            for(auto [value, count] : e.y) {
                auto it = s[e.to].lower_bound(make_pair(value, -1));
                if(it == s[e.to].end() || it -> first != value) {
                    A[e.to] = A[e.to] * Pow(value, count) % mod;
                    s[e.to].insert(make_pair(value, count));
                } else {
                    int count2 = it -> second;
                    A[e.to] = A[e.to] * Pow(value, count) % mod;
                    s[e.to].erase(it);
                    s[e.to].insert(make_pair(value, count + count2));
                }
            }
//             printf("%d ready: ", e.to + 1);
//             for(auto pa : s[e.to])
//                 printf("(%d, %d) ", pa.first, pa.second);
//             printf("\n");
        }
    }
    
    sort(adj[x].begin(), adj[x].end(), [&](const Edge &a, const Edge &b) {
        return s[a.to].size() > s[b.to].size();
    });
    
    for(Edge &e : adj[x]) {
        if(e.to != p) {
          //  printf("merging %d and %d\n", x + 1, e.to + 1);
            if(s[e.to].size() > s[x].size()) {
                swap(s[e.to], s[x]);
                swap(sum[e.to], sum[x]);
                swap(A[e.to], A[x]);
            }
            long long g = 1;
            for(auto [value, count] : s[e.to]) {
                auto it = s[x].lower_bound(make_pair(value, -1));
                if(it == s[x].end() || it -> first != value) {
                    s[x].insert(make_pair(value, count));
                } else {
                    int count2 = it -> second;
                    g = g * Pow(value, min(count, count2)) % mod;
                    if(count > count2) {
                        s[x].erase(it);
                        s[x].insert(make_pair(value, count));
                    }
                }
            }
         //   printf("g = %d\n", g);
            long long newSum = (A[x] * Inv(g) % mod) * sum[e.to] + (A[e.to] * Inv(g) % mod) * sum[x];
            sum[x] = newSum % mod;
            A[x] = (A[x] * A[e.to] % mod) * Inv(g) % mod;
        }
    }
   // printf("going back from %d: %d %d\n", x + 1, A[x], sum[x]);
    sum[x] += A[x];
}

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>d(n + 1, -1);
    for(int i = 2; i <= n; i++) {
        if(d[i] == -1) {
            d[i] = i;
            for(int j = i + i; j <= n; j += i)
                d[j] = i;
        }
    }
    vector<vector<Edge>>adj(n);
    for(int i = 1; i < n; i++) {
        int a, b, x, y; scanf("%d%d%d%d", &a, &b, &x, &y);
        int g = __gcd(x, y); x /= g; y /= g;
        swap(x, y);
        vector<pair<int, int>>X, Y;
        while(x != 1) {
            int D = d[x], cnt = 0;
            while(x % D == 0) {
                x /= D;
                cnt++;
            }
            X.emplace_back(D, cnt);
        }
        while(y != 1) {
            int D = d[y], cnt = 0;
            while(y % D == 0) {
                y /= D;
                cnt++;
            }
            Y.emplace_back(D, cnt);
        }
        adj[a - 1].emplace_back(b - 1, X, Y);
        adj[b - 1].emplace_back(a - 1, Y, X);
    }
    vector<long long>sum(n), A(n);
    vector<set<pair<int, int>>>s(n);
    DFS(0, -1, adj, s, sum, A);
    printf("%lld\n", sum[0] % mod);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
}
