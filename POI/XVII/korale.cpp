#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int MAX_N = 200007;
const long long mod[4] = {1000000007, 1000000009, 1000000021, 1000000033};

const int K = 2;

struct Hash {
    long long val[K];
    Hash() {}
    Hash(long long x) {
          for(int i = 0; i < K; i++)
              val[i] = x % mod[i];
    }
    Hash(long long _a, long long _b, long long _c, long long _d) {
          val[0] = _a;  val[1] = _b;  val[2] = _c;  val[3] = _d;
    }
    Hash operator* (Hash h) {
        Hash result(0);
        for(int i = 0; i < K; i++)
            result.val[i] = (val[i] * h.val[i]) % mod[i];
        return result;
    }
    Hash operator- (Hash h) {
        Hash result(0);
        for(int i = 0; i < K; i++)
            result.val[i] = (val[i] - h.val[i] + mod[i]) % mod[i];
        return result;
    }
    Hash operator+ (long long x) {
        Hash result(0);
        for(int i = 0; i < K; i++)
            result.val[i] = (val[i] + x) % mod[i];
        return result;
    }
};

struct HashComparator {
    bool operator() (const Hash &a, const Hash &b) const {
        for(int i = 0; i < K; i++)
            if(a.val[i] != b.val[i])
                return a.val[i] < b.val[i];
        return false;
    }
};

const Hash B(200003, 200009, 200017, 200023);

Hash L[MAX_N], R[MAX_N], P[MAX_N];
int n, arr[MAX_N], result[MAX_N];

Hash GetHashL(int a, int b) {
    Hash l = a == 0 ? Hash(0) : (L[a - 1] * P[b - a + 1]);
    return L[b] - l;
}

Hash GetHashR(int a, int b) {
    Hash r = b == n - 1 ? Hash(0) : (R[b + 1] * P[b - a + 1]);
    return R[a] - r;
}

int Get(int len) {
    set<Hash, HashComparator>s;
    int result = 0;
    for(int i = 0; i + len <= n; i += len) {
        Hash l = GetHashL(i, i + len - 1);
        Hash r = GetHashR(i, i + len - 1);
        if(s.count(l) == 0 && s.count(r) == 0) {
            s.insert(l);
            s.insert(r);
            result++;
        }
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    
    P[0] = Hash(1);
    for(int i = 1; i <= n; i++)
        P[i] = P[i - 1] * B;
    
    L[0] = Hash(arr[0]);
    for(int i = 1; i < n; i++)
        L[i] = (L[i - 1] * B) + arr[i];
    
    R[n - 1] = Hash(arr[n - 1]);
    for(int i = n - 2; i >= 0; i--)
        R[i] = (R[i + 1] * B) + arr[i];
    
    int hi = 0;
    for(int i = 1; i <= n; i++) {
        result[i] = Get(i);
        hi = max(hi, result[i]);
    }
    
    int amount = 0;
    for(int i = 1; i <= n; i++)
        if(result[i] == hi)
            amount++;
        
    cout << hi << ' ' << amount << '\n';
    for(int i = 1; i <= n; i++)
        if(result[i] == hi)
            cout << i << ' ';
    cout << '\n';
    
    return 0;
}
