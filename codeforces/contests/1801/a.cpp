#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <algorithm>
#include <bitset>

using namespace std;

const int MAX_N = 256;

int a[MAX_N][MAX_N];

void test_case() {
    int n, m; cin >> n >> m;
    cout << n * m << '\n';
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << a[i][j] << ' ';
        }
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int x = 0;
    for(int i = 0; i < MAX_N; i += 2) { 
        for(int j = 0; j < MAX_N; j += 2) {
            a[i][j] = x++;
            a[i][j + 1] = x++;
            a[i + 1][j] = x++;
            a[i + 1][j + 1] = x++;
        }
    }
    int t; cin >> t;
    while(t--)
        test_case();
    
    return 0;
}
