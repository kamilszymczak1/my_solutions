#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

const long long mod = 1'000'000'007;

int Len(int x) {
    int result = 0;
    while(x) {
        result++;
        x /= 2;
    }
    return result;
}

int Conv(int x) {
    vector<int>result;
    while(x) {
        if(x % 2 == 1) {
            x /= 2;
        } else if((x / 2) % 2 == 0) {
            x /= 4;
        } else {
            break;
        }
    }
    return x;
}

void TestCase() {
    int n, p; cin >> n >> p;
    vector<long long>a(n), fib(p + 7);
    fib[0] = fib[1] = 1;
    for(int i = 2; i < p + 7; i++)
        fib[i] = (fib[i - 1] + fib[i - 2]) % mod;
    for(int i = 1; i < p + 7; i++)
        fib[i] = (fib[i] + fib[i - 1]) % mod;
    map<int, vector<int>>m;
    for(int i = 0; i < n; i++) {
        cin >> a[i]; int c = Conv(a[i]);
        m[c].push_back(a[i]);
    }
    long long result = 0;
    for(auto [pref, vec] : m) {
        sort(vec.begin(), vec.end());
        set<int>used;
        for(int x : vec) {
            vector<int>v; 
            for(int y = x; y; y /= 2) 
                v.push_back(y % 2);
            reverse(v.begin(), v.end());
            int prefix = 0, good = 1;
            for(int i = 0; i < v.size(); i++) {
                prefix = prefix * 2 + v[i];
                if(used.find(prefix) != used.end())
                    good = 0;
            }
            if(good && v.size() <= p) {
                used.insert(x);
                result = (result + fib[p - v.size()]) % mod;
            }
        }
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
