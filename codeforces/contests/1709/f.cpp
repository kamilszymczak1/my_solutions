#include <cstdio>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

const long long mod = 998244353;
const long long primitive_root = 3;

struct Mint {
    int t;
    Mint() : t(0) {}
    Mint(int _t) : t(_t) {}
    int abs() { return t; }
};

inline Mint operator+ (Mint a, Mint b) { return Mint((a.t + b.t >= mod) ? (a.t + b.t - mod) : (a.t + b.t)); }
inline Mint operator- (Mint a, Mint b) { return Mint((a.t - b.t < 0) ? (a.t - b.t + mod) : (a.t - b.t)); }
inline Mint operator* (Mint a, Mint b) { return Mint((1ll * a.t * b.t) % mod); }

inline Mint power(Mint a, int exp) {
    Mint result(1), aPow = a;
    for(; exp; exp /= 2) {
        if(exp % 2 == 1)
            result = result * aPow;
        aPow = aPow * aPow;
    }
    return result;
}

inline Mint inverse(Mint a) { return power(a, mod - 2); }

struct Squarer {
    int max_h;
    vector<vector<Mint>>w[2];
    vector<vector<int>>rev;
    Mint unity_root;
    Squarer(int _max_h, int _unity_root) {
        unity_root = Mint(_unity_root);
        max_h = _max_h;
        
        for(int j = 0; j < 2; j++)
            w[j].resize(max_h + 1);
        for(int h = 0; h <= max_h; h++) {
            vector<Mint>step = { power(unity_root, 1 << (max_h - h)), inverse(power(unity_root, 1 << (max_h - h))) };
            for(int j = 0; j < 2; j++) {
                w[j][h].resize(1 << h, Mint(1));
                for(int i = 1; i < (1 << h); i++)
                    w[j][h][i] = w[j][h][i - 1] * step[j];
            }
        }
        rev.resize(max_h + 1);
        for(int h = 0; h <= max_h; h++) {
            rev[h].resize(1 << h);
            rev[h][0] = 0;
            int bit = 0;
            for(int i = 1; i < (1 << h); i++) {
                while((1 << (bit + 1)) <= i)
                    bit++;
                rev[h][i] = rev[h][i ^ (1 << bit)] | (1 << (h - bit - 1));
            }
        }
        
    }
    
    void DFT(vector<Mint>&a, int h, bool inv) {
        int n = a.size();
        for(int i = 0; i < n; i++) {
            if(rev[h][i] < i) {
                swap(a[rev[h][i]], a[i]);
            }
        }
        for(int bit = 0; bit < h; bit++) {
            int len = 1 << bit;
            for(int i = 0; i < n; i += len * 2) {
                for(int j = 0; j < len; j++) {
                    Mint x = a[i + j], y = a[i + j + len] * w[inv][bit + 1][j];
                    a[i + j] = x + y;
                    a[i + j + len] = x - y;
                }
            }
        }
        
        if(inv) {
            Mint m = inverse(n);
            for(auto &x : a)
                x = x * m;
        }
    }
    
    void square(vector<Mint>&a) {
        int h = 32 - __builtin_clz(2 * (int)a.size() - 1), n = a.size();
        a.resize(1 << h, 0);
        DFT(a, h, false);
        for(auto &x : a)
            x = x * x;
        DFT(a, h, true);
        a.resize(2 * n - 1);
    }
    
};


int main() {
    
    Squarer squarer(19, power(Mint(primitive_root), (mod - 1) / (1 << 19)).abs());
    
    int n, k, f; scanf("%d%d%d", &n, &k, &f);
    vector<Mint>dp(k + 1, Mint(1));
    for(int i = 1; i < n; i++) {
        squarer.square(dp);
        for(int j = (int)dp.size() - 2; j >= 0; j--)
            dp[j] = dp[j] + dp[j + 1];
        for(int j = 0; j <= k; j++)
            dp[j] = (dp[j] - dp[j + 1]) * Mint(k - j + 1) + dp[j + 1];
        dp.resize(k + 1);
    }
    squarer.square(dp);
    printf("%d\n", f < (int)dp.size() ? dp[f].abs() : 0);
    
    return 0;
}
