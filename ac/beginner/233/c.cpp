#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

long long Gen(int x, long long p, vector<vector<long long>>&a, long long X) {
    if(x == a.size())
        return p == X;
    long long result = 0;
    for(long long y : a[x]) {
        if(((long double)p) * y <= (long double)X)
            result += Gen(x + 1, p * y, a, X);
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    long long x; cin >> x;
    vector<vector<long long>>a(n);
    for(int i = 0; i < n; i++) {
        int l; cin >> l;
        for(int j = 0; j < l; j++) {
            int x; cin >> x;
            a[i].push_back(x);
        }
    }
    
    cout << Gen(0, 1, a, x) << '\n';
    
    return 0;
}
