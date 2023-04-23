#include <iostream>
#include <vector>
#include <cstdio>
#include <ctime>
#include <bitset>

using namespace std;

constexpr int MAX_N = 200007;

uint randint32() {
    int result = 0;
    for(int i = 0; i < 4; i++)
        result = (result << 8) | (rand() & 0xff);
    return result;
}

long long Solve(long long mask, vector<long long>&v, int n, int m) {
    vector<int>s(n, 0);
    int bitCount = 0;
    cout << bitset<4>(mask).to_string() << '\n';
    for(int i = 0; i < m; i++) {
        if(mask & (1 << i)) {
            bitCount++;
            for(int j = 0; j < n; j++) {
                s[j] = s[j] * 2 + (v[j] & (1 << i));
            }
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    srand(time(NULL));
    int n, m, p;
    cin >> n >> m >> p;
    vector<long long>v(n, 0);
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(int j = 0; j < m; j++)
            v[i] = v[i] * 2 + s[j] - '0';
    }
    
    long long result = 0;
    for(int i = 0; i < 10; i++) {
        int ind = randint32() % n;
        long long bestMask = Solve(v[ind], v, n, m);
        if(__builtin_popcount(bestMask) > __builtin_popcount(result))
            result = bestMask;
    }
    
    for(int i = 0; i < m; i++, result >>= 1)
        cout << (result & 1);
    cout << '\n'; 
    return 0;
}
