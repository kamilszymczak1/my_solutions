#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
#include <bitset>

using namespace std;

int LCM(int a, int b) {
    return (a * b) / __gcd(a, b);
}

void TestCase() {
    int n, m; cin >> n >> m;
    vector<int>factor(n + 1, -1);
    for(int i = 2; i <= n; i++) {
        if(factor[i] == -1) {
            factor[i] = i;
            for(int j = i + i; j <= n; j += i) {
                factor[j] = i;
            }
        }
    }
    const int K = 20;
    //vector<vector<int>>help(20, vector<int>(m, 0));
    vector<long long>contribution(1 << K, 0);
    for(int i = 1; i < (1 << K); i++) {
        int mi = 20, lcm = -1;
        for(int j = 0; j < K; j++) {
            if((i >> j) & 1) {
                mi = min(mi, j + 1);
                lcm = lcm == -1 ? j + 1 : LCM(lcm, j + 1);
            }
        }
        contribution[i] = (mi * m) / lcm;
        if(__builtin_popcount(i) % 2 == 0)
            contribution[i] *= -1;
    }
    for(int i = 0; i < K; i++) {
        for(int j = 0; j < (1 << K); j++) {
            if((j >> i) & 1) {
                contribution[j] += contribution[j ^ (1 << i)];
            }
        }
    }
    vector<long long>newContribution(K, 0);
    for(int i = 0; i < K; i++)
        newContribution[i] = contribution[(1 << (i + 1)) - 1] - contribution[(1 << i) - 1];
    swap(contribution, newContribution);
    vector<int>count(n + 1);
    long long result = 1;
    for(int row = 2; row <= n; row++) {
        vector<pair<int, int>>factorization;
        int x = row, g = -1;
        while(x != 1) {
            int cnt = 0, div = factor[x];
            while(x % div == 0) {
                x /= div;
                cnt++;
            }
            factorization.emplace_back(div, cnt);
            g = g == -1 ? cnt : __gcd(g, cnt);
        }
        int number = 1;
        for(auto &[a, cnt] : factorization) {
            cnt /= g;
            for(int i = 0; i < cnt; i++)
                number *= a;
        }
        
        //occ[row] = contribution[numbers[number]];
        result += contribution[count[number]];
        count[number]++;
    }
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
