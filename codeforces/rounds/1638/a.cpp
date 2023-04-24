#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<int>p(n), pos(n);
    for(int i = 0; i < n; i++) {
        cin >> p[i]; p[i]--;
        pos[p[i]] = i;
    }
    for(int i = 0; i < n; i++) { 
        if(pos[i] != i) {
            reverse(p.begin() + i, p.begin() + pos[i] + 1);
            break;
        }
    }
    for(int x : p)
        cout << x + 1 << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
