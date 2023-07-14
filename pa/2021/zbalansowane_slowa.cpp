#include <iostream>
#include <map>

#define f(k, x, i) (k * x - i + MAX_N)

using namespace std;

const long long MAX_N = 300'007;

map<long long, int>m[8];
long long cnt[3][8];
string s;

long long H(int i, int mask) {
    switch(mask) {
        case 1: return f(1, cnt[0][1], i); break;
        case 2: return f(1, cnt[1][2], i); break;
        case 4: return f(1, cnt[2][4], i); break;
        case 3: return (f(2, cnt[0][3], i) << 20) + f(2, cnt[1][3], i); break;
        case 5: return (f(2, cnt[0][5], i) << 20) + f(2, cnt[2][5], i); break;
        case 6: return (f(2, cnt[1][6], i) << 20) + f(2, cnt[2][6], i); break;
        case 7: return (f(3, cnt[0][7], i) << 40) + (f(3, cnt[1][7], i) << 20) + f(3, cnt[2][7], i);
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> s;
    int n = s.size();
    for(int i = 1; i < 8; i++)
        m[i][H(0, i)] = 1;
    long long result = 0;
    for(int i = 0; i < (int)s.size(); i++) {
        for(int mask = 1; mask < 8; mask++) {
            if(mask & (1 << (s[i] - 'a'))) {
                cnt[s[i] - 'a'][mask]++;
                result += m[mask][H(i + 1, mask)];
            } else {
                cnt[0][mask] = cnt[1][mask] = cnt[2][mask] = 0;
                m[mask].clear();
            }
            m[mask][H(i + 1, mask)]++;
        }
    }
    cout << result << '\n';
    return 0;
}
