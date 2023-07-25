#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n, x, a; cin >> n >> x;
    for(int i = 0; i < n; i++) {
        int a; cin >> a;
        if(i & 1)
            a--;
        x -= a;
    }
    
    cout << (x >= 0 ? "Yes" : "No") << '\n';
    
    return 0;
}
