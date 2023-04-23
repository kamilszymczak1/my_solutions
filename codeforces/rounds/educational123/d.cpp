#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const long long mod = 998244353;

void TestCase() {
    int n, m, k, q; cin >> n >> m >> k >> q;
    vector<pair<int, int>>Q;
    //map<pair<int, int>, int>s;
    for(int i = 0; i < q; i++) {
        int x, y; cin >> x >> y; x--; y--;
        Q.push_back(make_pair(x, y));
    }
    vector<bool>rowPainted(n, false), columnPainted(m, false);
    int rowsPainted = 0, columnsPainted = 0;
    long long result = 1;
    for(int i = q - 1; i >= 0; i--) {
        int x = Q[i].first, y = Q[i].second;
        if(rowPainted[x] && columnPainted[y]) {
            //valid[i] = false;
        } else {
            result = (result * k) % mod;
            if(!rowPainted[x]) {
                rowPainted[x] = true;
                rowsPainted++;
            }
            if(!columnPainted[y]) {
                columnPainted[y] = true;
                columnsPainted++;
            }
            
            if(rowsPainted == n && columnsPainted != m) {
                for(int j = 0; j < m; j++)
                    columnPainted[j] = true;
                columnsPainted = m;
            }
            if(rowsPainted != n && columnsPainted == m) {
                for(int j = 0; j < n; j++)
                    rowPainted[j] = true;
                rowsPainted = n;
            }
        }
    }
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
