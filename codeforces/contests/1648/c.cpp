#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 200'007;
const long long mod = 998244353;
long long cnt[MAX_N], t[MAX_N];
long long fac[MAX_N + 7], inv[MAX_N + 7], invFac[MAX_N + 7];
int n, m;

struct SegTree {
    vector<long long>values;
    int leafCount;
    SegTree(int n) {
        for(leafCount = 1; leafCount < n; leafCount *= 2) {}
        values.resize(leafCount * 2, 1);
        for(int i = leafCount - 1; i; i--)
            values[i] = values[i * 2] + values[i * 2 + 1];
    }
    long long Prefix(int a) {
        long long result = values[a + leafCount];
        for(a += leafCount; a > 1; a /= 2)
            result += values[a - 1] * (a % 2);
        return result % mod;
    }
    void Mult(int x, long long value) {
        values[x + leafCount] = values[x + leafCount] * value % mod;
        for(x = (x + leafCount) / 2; x; x /= 2)
            values[x] = (values[x * 2] + values[x * 2 + 1]) % mod;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    fac[0] = fac[1] = invFac[0] = invFac[1] = inv[1] = 1;
    for(int i = 2; i <= MAX_N; i++) {
        inv[i] = mod - (mod / i) * inv[mod % i] % mod;
        fac[i] = fac[i - 1] * i % mod;
        invFac[i] = invFac[i - 1] * inv[i] % mod;
    }
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt[x - 1]++;
    }
    
    for(int i = 0; i < m; i++) {
        cin >> t[i];
        t[i]--;
    }
    
    long long all = fac[n];
    for(int i = 0; i < MAX_N; i++)
        all = all * invFac[cnt[i]] % mod;
    
    SegTree T(MAX_N);
    
    for(int i = 0; i < MAX_N; i++)
        T.Mult(i, (all * inv[n] % mod) * cnt[i] % mod);
    
    long long result = 0, offset = 1;
    for(int p = 0; p <= min(n - 1, m - 1); p++) {
        if(t[p] != 0)
            result = (result + T.Prefix(t[p] - 1) * offset) % mod;
        if(cnt[t[p]] == 0) {
            cout << result << '\n';
            return 0;
        }
        long long A = cnt[t[p]] * inv[n - p - 1] % mod;
        offset = (offset * A) % mod;
        long long B = inv[cnt[t[p]]] * (n - p - 1) % mod;
        T.Mult(t[p], ((A - inv[n - p - 1] + mod) * B) % mod);
        cnt[t[p]]--;
    }
    cout << (result + (n < m)) % mod << '\n';
    
    return 0;
}
