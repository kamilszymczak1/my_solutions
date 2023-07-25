#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    int n; cin >> n;
    vector<int>r(n), c(n);
    for(int i = 0; i < n; i++)
        cin >> r[i];
    for(int i = 0; i < n; i++)
        cin >> c[i];
    
    int q; cin >> q;
    while(q--) {
        int R, C; cin >> R >> C; R--; C--;
        if(c[C] >= n - r[R] + 1) {
            cout << "#";
        } else {
            cout << ".";
        }
    }
    cout << '\n';
    
    return 0;
}
