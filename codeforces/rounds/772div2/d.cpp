#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

const long long mod = 1'000'000'007;

void TestCase() {
    int n, p; cin >> n >> p;
    vector<long long>a(n), fib(p + 7, 1);
    for(int i = 2; i < p + 7; i++)
        fib[i] = (fib[i - 1] + fib[i - 2]) % mod;
    for(int i = 1; i < p + 7; i++)
        fib[i] = (fib[i] + fib[i - 1]) % mod;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    sort(a.begin(), a.end());
    set<int>used;
    int result = 0;
    for(int i = 0; i < n; i++) {
        int x = a[i];
        vector<int>v;
        for(int y = x; y; y /= 2)
            v.push_back(y % 2);
        reverse(v.begin(), v.end());
        vector<bool>ok(v.size() + 1, false);
        ok[v.size()] = true;
        for(int i = (int)v.size() - 1; i >= 0; i--) {
            if(v[i] == 1) {
                ok[i] = ok[i + 1];
            } else if(i <= (int)v.size() - 2){
                ok[i] = ok[i + 2] & (v[i + 1] == 0);
            }
        }
        int prefix = 0, occurence = 0;
        for(int i = 0; i < (int)v.size(); i++) {
            prefix = prefix * 2 + v[i];
            
            occurence |= (used.find(prefix) != used.end()) && ok[i + 1];
        }
        if(!occurence && v.size() <= p) {
            result = (result + fib[p - v.size()]) % mod;
            used.insert(prefix);
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
