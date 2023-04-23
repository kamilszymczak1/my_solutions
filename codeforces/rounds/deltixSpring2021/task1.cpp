#include <iostream>
#include <vector>

using namespace std;

constexpr int inf = 1000000001;

void TestCase() {
    int n, m;
    string s;
    cin >> n >> m >> s;
    vector<int>l(n, 0), r(n, 0);
    l[0] = s[0] == '1' ? 0 : inf;
    for(int i = 1; i < n; i++) { 
        l[i] = s[i] == '1' ? 0 : l[i - 1] + 1;
    }
    r[n - 1] = s[n - 1] == '1' ? 0 : inf;
    for(int i = n - 2; i >= 0; i--) {
        r[i] = s[i] == '1' ? 0 : r[i + 1] + 1;
    }
    for(int i = 0; i < n; i++) {
        if(l[i] != r[i] && min(l[i], r[i]) <= m)
            s[i] = '1';
    }
    cout << s << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
