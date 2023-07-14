#include <iostream>
    
using namespace std;
    
int main() {
    ios_base::sync_with_stdio(0);
    int n, m, c; cin >> n >> m >> c;
    
    pair<int, int>best = {-1, -1};
    int best_err = 1 << 30;
    
    for(int i = 0; i * m <= n * 2; i++) {
        int remaining = n - i * m;
        
        if(remaining < 0) {
            if(abs(n - i * m) < best_err) {
                best_err = abs(n - i * m);
                best = make_pair(i, 0);
            }
        } else {
            int d = remaining / c;
            if(abs(remaining - d * c) < best_err) {
                best = make_pair(i, d);
                best_err = abs(remaining - d * c);
            }
            d++;
            if(abs(remaining - d * c) < best_err) {
                best = make_pair(i, d);
                best_err = abs(remaining - d * c);
            }
        } 
    }
    
    
    
    cout << best.first << ' ' << best.second << '\n';
    
    return 0;
}
