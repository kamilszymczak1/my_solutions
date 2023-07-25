#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
    
using namespace std;
    
const int RANGE = 100'007;
const long long mod = 998244353;
    
struct SegTreeShift {
    
    struct Node {
        int lazy_shift;
        vector<int>values;
        Node() {}
        Node(int _size) : lazy_shift(0) {
            values.reserve(_size);
            values.resize(_size, 0);
        }
    };
    int w;
    vector<int>dummy;
    vector<Node>nodes;
    int leaf_count, a, b;
    
    SegTreeShift(int n, int _w) {
        w = _w;
        dummy.resize(w);
        for(leaf_count = 1; leaf_count < n; leaf_count *= 2) {}
        nodes.resize(leaf_count * 2, Node(w));
    }
    
    void shift_vector(vector<int>&v, int k) {
        for(int i = 0; i < w; i++)
            dummy[i] = v[i];
        for(int i = 0; i < w; i++) {
            int index = i - k < 0 ? (i - k + w) : (i - k);
            v[i] = dummy[index];
        }
    }
    
    void merge(int v) {
        for(int i = 0; i < w; i++)
            nodes[v].values[i] = nodes[v * 2].values[i] + nodes[v * 2 + 1].values[i];
    }
    
    void push(int v) {
        if(nodes[v].lazy_shift == 0)
            return;
        for(int i = 0; i < 2; i++) {
            shift_vector(nodes[v * 2 + i].values, nodes[v].lazy_shift);
            nodes[v * 2 + i].lazy_shift += nodes[v].lazy_shift;
            if(nodes[v * 2 + i].lazy_shift >= w)
                nodes[v * 2 + i].lazy_shift -= w;
        }
        nodes[v].lazy_shift = 0;
    }
    
    void shift(int _a, int _b, int k) {
        a = _a; b = _b + 1;
        shift(0, leaf_count, 1, k);
    }
    void shift(int lo, int hi, int v, int k) {
        if(a <= lo && hi <= b) {
            shift_vector(nodes[v].values, k);
            nodes[v].lazy_shift += k;
            if(nodes[v].lazy_shift >= w)
                nodes[v].lazy_shift -= w;
            return;
        }
        if(b <= lo || hi <= a)
            return;
        push(v);
        const int mid = (lo + hi) / 2;
        shift(lo, mid, v * 2, k);
        shift(mid, hi, v * 2 + 1, k);
        merge(v);
    }
    
    void push_path(int lo, int hi, int v, int x) {
        if(hi - lo > 1) {
            push(v);
            int mid = (lo + hi) / 2;
            if(x < mid) {
                push_path(lo, mid, v * 2, x);
            } else {
                push_path(mid, hi, v * 2 + 1, x);
            }
        }
    }
    
    void add(int x, int y, int value) {
        push_path(0, leaf_count, 1, x);
        for(x += leaf_count; x; x >>= 1)
            nodes[x].values[y] += value;
    }
};
    
struct SegTreeAddSum {
    vector<int>sums;
    int leaf_count;
    SegTreeAddSum(int n) {
        for(leaf_count = 1; leaf_count < n; leaf_count *= 2) {}
        sums.reserve(leaf_count * 2);
        sums.resize(leaf_count * 2);
    }
    void add(int x, int value) {
        for(x += leaf_count; x > 1; x >>= 1) {
            sums[x] += value;
        }
    }
    int prefix_sum(int x) {
        int result = sums[x + leaf_count];
        for(x += leaf_count; x > 1; x >>= 1)
            result += sums[x - 1] * (x & 1);
        return result;
    }
};
    
struct SegTreeCount {
    struct Node {
        long long lazy_inc;
        vector<long long>p;
        Node(int _size) : lazy_inc(0) {
            p.resize(_size + 1, 0);
        }
    };
    vector<Node>nodes;
    vector<vector<long long>>choice;
    vector<long long>t_pow;
    int leaf_count, k, a, b;
    SegTreeCount(int n, int _k) {
        k = _k;
        for(leaf_count = 1; leaf_count < n; leaf_count *= 2) {}
        nodes.resize(leaf_count * 2, Node(k));
        choice.resize(k + 1);
        for(int i = 0; i <= k; i++) {
            choice[i].resize(i + 1);
            choice[i][0] = choice[i][i] = 1;
            for(int j = 1; j < i; j++)
                choice[i][j] = (choice[i - 1][j - 1] + choice[i - 1][j]) % mod;
        }
        t_pow.resize(k + 1);
    }
    
    void push(int v) {
        if(nodes[v].lazy_inc == 0)
            return;
        t_pow[0] = 1;
        for(int i = 1; i <= k; i++)
            t_pow[i] = t_pow[i - 1] * nodes[v].lazy_inc % mod;
        for(int s = 0; s < 2; s++) {
            for(int i = k; i > 0; i--) {
                for(int j = 0; j < i; j++) {
                    long long coeff = choice[i][j] * nodes[v * 2 + s].p[j] % mod;
                    nodes[v * 2 + s].p[i] = (nodes[v * 2 + s].p[i] + coeff * t_pow[i - j]) % mod;
                }
            }
            nodes[v * 2 + s].lazy_inc += nodes[v].lazy_inc;
            if(nodes[v * 2 + s].lazy_inc >= mod)
                nodes[v * 2 + s].lazy_inc -= mod;
        }
        nodes[v].lazy_inc = 0;
    }
    
    void increase(int _a, int _b, int t) {
        a = _a; b = _b + 1;
        increase(0, leaf_count, 1, t);
    }
    void increase(int lo, int hi, int v, int t) {
        if(a <= lo && hi <= b) {
            t_pow[0] = 1;
            for(int i = 1; i <= k; i++)
                t_pow[i] = t_pow[i - 1] * t % mod;
            for(int i = k; i > 0; i--) {
                for(int j = 0; j < i; j++) {
                    long long coeff = choice[i][j] * nodes[v].p[j] % mod;
                    nodes[v].p[i] = (nodes[v].p[i] + coeff * t_pow[i - j]) % mod;
                }
            }
            nodes[v].lazy_inc += t;
            if(nodes[v].lazy_inc >= mod)
                nodes[v].lazy_inc -= mod;
            return;
        }
        if(b <= lo || hi <= a)
            return;
        push(v);
        const int mid = (lo + hi) / 2;
        increase(lo, mid, v * 2, t);
        increase(mid, hi, v * 2 + 1, t);
        for(int i = 0; i <= k; i++) {
            nodes[v].p[i] = nodes[v * 2].p[i] + nodes[v * 2 + 1].p[i];
            if(nodes[v].p[i] >= mod)
                nodes[v].p[i] -= mod;
        }
    }
    
    void push_path(int lo, int hi, int v, int x) {
        if(hi - lo > 1) {
            push(v);
            int mid = (lo + hi) / 2;
            if(x < mid) {
                push_path(lo, mid, v * 2, x);
            } else {
                push_path(mid, hi, v * 2 + 1, x);
            }
        }
    }
    
    void add(int x, long long order, long long value) {
        push_path(0, leaf_count, 1, x);
        t_pow[0] = value;
        for(int i = 1; i <= k; i++)
            t_pow[i] = t_pow[i - 1] * order % mod;
        for(x += leaf_count; x; x >>= 1) {
            for(int i = 0; i <= k; i++) {
                nodes[x].p[i] += t_pow[i];
                if(nodes[x].p[i] >= mod)
                    nodes[x].p[i] -= mod;
            }
        }
    }
};
    
long long mod_pow(long long x, long long exp) {
    long long result = 1;
    for(; exp; exp >>= 1) {
        if(exp & 1)
            result = result * x % mod;
        x = x * x % mod;
    }
    return result;
}
    
long long get_remainder(vector<SegTreeShift>&t_shift, int w, int k, vector<vector<long long>>&quick_pow) {
    long long answer = 0;
    for(int i = 0; i < w; i++) {
        for(int j = 0; j < w; j++) {
            long long value = i * quick_pow[j][k] % w;
            long long count = t_shift[i].nodes[1].values[j];
            answer += value * count;
        }
    }
    return answer % mod;
}
    
void init(vector<int>a, SegTreeAddSum &t_order, vector<SegTreeShift>&t_shift, SegTreeCount &t_count, int w, int k) {
    sort(a.begin(), a.end());
    for(int i = 1; i <= (int)a.size(); i++) {
        t_order.add(a[i - 1], 1);
        t_shift[a[i - 1] % w].add(a[i - 1], i % w, 1);
        t_count.add(a[i - 1], i, a[i - 1]);
    }
}
    
int main() {
    int n, k, w; scanf("%d%d%d", &n, &k, &w);
    
    SegTreeAddSum t_order(RANGE);
    vector<SegTreeShift>t_shift(w, SegTreeShift(RANGE, w));
    SegTreeCount t_count(RANGE, k);
    
    vector<int>a(n);
    for(int &x : a)
        scanf("%d", &x);
    
    init(a, t_order, t_shift, t_count, w, k);
    
    long long inv_w = mod_pow(w, mod - 2);
    
    vector<vector<long long>>quick_pow_mod_w(6, vector<long long>(6, 0));
    for(int i = 0; i <= 5; i++) {
        quick_pow_mod_w[i][0] = 1;
        for(int j = 1; j <= 5; j++)
            quick_pow_mod_w[i][j] = quick_pow_mod_w[i][j - 1] * i % w;
    }
    
    int q; scanf("%d", &q);
    while(q--) {
        int pos, x, my_order; 
        scanf("%d%d", &pos, &x); pos--;
        
        my_order = t_order.prefix_sum(a[pos]);
        t_shift[a[pos] % w].add(a[pos], my_order % w, -1);
        t_order.add(a[pos], -1);
        for(int i = 0; i < w; i++) {
            if(a[pos] + 1 <= RANGE - 1)
                t_shift[i].shift(a[pos] + 1, RANGE - 1, w - 1);
        }
        
        
        t_count.add(a[pos], my_order, (mod - a[pos]) % mod);
        t_count.increase(a[pos] + 1, RANGE - 1, mod - 1);
        
        t_order.add(x, 1);
        my_order = t_order.prefix_sum(x);
        t_shift[x % w].add(x, my_order % w, 1);
        for(int i = 0; i < w; i++)
            if(x + 1 <= RANGE - 1)
                t_shift[i].shift(x + 1, RANGE - 1, w == 1 ? 0 : 1);
        t_count.add(x, my_order, x);
        t_count.increase(x + 1, RANGE - 1, 1);
        a[pos] = x;
        
        
        long long total = t_count.nodes[1].p[k];
        long long remainder = get_remainder(t_shift, w, k, quick_pow_mod_w);
        total = (total - remainder + mod) * inv_w % mod;
        printf("%lld\n", total);
    }
    
    return 0;
}
