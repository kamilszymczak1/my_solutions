#include <cstdio>
#include <vector>
    
using namespace std;
    
const int mod = 998244353;
const int primitive_root = 3;
    
int mod_pow(int a, int exp) {
    int result = 1;
    for(; exp; exp >>= 1, a = (1ll * a * a) % mod) {
        if(exp & 1)
            result = (1ll * result * a) % mod;
    }
    return result;
}
    
int inverse(int x) { return mod_pow(x, mod - 2); }
    
struct PolynomialMultiplier {
    vector<vector<int>>w[2], rev;
    int max_h, unity_root = 0;
    PolynomialMultiplier(int _max_h, int _unity_root) {
        max_h = _max_h;
        unity_root = _unity_root;
        for(int j = 0; j < 2; j++)
            w[j].resize(max_h + 1);
        rev.resize(max_h + 1);
        
        for(int h = 1; h <= max_h; h++) {
            vector<int>step = {mod_pow(unity_root, 1 << (max_h - h)), inverse(mod_pow(unity_root, 1 << (max_h - h))) };
            for(int j = 0; j < 2; j++) {
                w[j][h].resize(1 << (h - 1), 1);
                for(int i = 1; i < (1 << (h - 1)); i++)
                    w[j][h][i] = (1ll * w[j][h][i - 1] * step[j]) % mod;
            }
            
            int bit = 0;
            rev[h].resize(1 << h);
            for(int i = 1; i < (1 << h); i++) {
                while((1 << (bit + 1)) <= i)
                    bit++;
                rev[h][i] = rev[h][i ^ (1 << bit)] | (1 << (h - bit - 1));
            }
        }
    }
    
    void DFT(vector<int>&a, int h, bool inv) {
        int n = a.size();
        for(int i = 0; i < n; i++) {
            if(rev[h][i] < i) {
                swap(a[i], a[rev[h][i]]);
            }
        }
        for(int bit = 0; bit < h; bit++) {
            int len = 1 << bit;
            for(int i = 0; i < n; i += len * 2) {
                for(int j = 0; j < len; j++) {
                    int x = a[i + j], y = (1ll * a[i + j + len] * w[inv][bit + 1][j]) % mod;
                    a[i + j] = (x + y >= mod) ? (x + y - mod) : (x + y);
                    a[i + j + len] = (x - y < 0) ? (x - y + mod) : (x - y);
                }
            }
        }
        
        if(inv) {
            int m = inverse(n);
            for(int &x : a)
                x = (1ll * x * m) % mod;
        }
    }
    
    vector<int> multiply(vector<int>&a, vector<int>&b) {
        int s = (int)a.size() + (int)b.size() - 1;
        int h = 32 - __builtin_clz(s);
        a.resize(1 << h);
        b.resize(1 << h);
        DFT(a, h, false);
        DFT(b, h, false);
        vector<int>c((1 << h));
        for(int i = 0; i < (1 << h); i++)
            c[i] = (1ll * a[i] * b[i]) % mod;
        DFT(c, h, true);
        c.resize(s);
        return c;
    }
};
    
void solve(vector<int>&A, vector<int>&color, vector<int>&len_count, PolynomialMultiplier &multi) {
    int n = A.size();
    vector<int>a(n), b(n), c(n), d(n);
    int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += A[i] * (1 - color[i]);
        if(sum >= mod)
            sum -= mod;
        a[i] = sum * color[i];
        c[i] = color[i];
        b[n - 1 - i] = a[i];
        d[n - 1 - i] = color[i];
    }
    vector<int>e = multi.multiply(a, d), f = multi.multiply(b, c);
    for(int len = 3; len <= n; len++) {
        len_count[len] += e[len + n - 2];
        if(len_count[len] >= mod)
            len_count[len] -= mod;
        len_count[len] -= f[len + n - 2];
        if(len_count[len] < 0)
            len_count[len] += mod;
    }
}
    
int main() {
    
    PolynomialMultiplier multi(19, mod_pow(primitive_root, (mod - 1) / (1 << 19)));
    
    int n; scanf("%d", &n);
    vector<int>color(n);
    char *c = new char[n + 1];
    scanf("%s", c);
    for(int i = 0; i < n; i++)
        color[i] = c[i] == 'W';
    delete[] c;
    vector<int>A(n);
    for(auto &x : A) {
        scanf("%d", &x);
        if(x >= mod)
            x -= mod;
    }
    
    vector<int>len_count(n + 1, 0);
    solve(A, color, len_count, multi);
    for(int &x : color)
        x = 1 - x;
    solve(A, color, len_count, multi);
    
    vector<int>fact(n + 1, 1), inv(n + 1, 1);
    for(int i = 1; i <= n; i++)
        fact[i] = (1ll * fact[i - 1] * i) % mod;
    int invFact = inverse(fact[n]);
    for(int i = n; i > 0; i--) {
        inv[i] = (1ll * invFact * fact[i - 1]) % mod;
        invFact = (1ll * invFact * i) % mod;
    }
    
    int result = 0;
    for(int len = 3; len <= n; len++) {
        int coeff = 1;
        for(int i = -2; i <= 0; i++)
            coeff = (1ll * coeff * inv[len + i]) % mod;
        result = (result + 1ll * coeff * len_count[len]) % mod;
    }
    result = (2ll * result * fact[n]) % mod;
    printf("%d\n", result);
    
    return 0;
}
