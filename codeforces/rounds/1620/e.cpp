#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 500007;

int Find(int x, vector<int>&f) {
    return f[x] == -1 ? x : f[x] = Find(f[x], f);
}

int main() {
    ios_base::sync_with_stdio(0);
    int q; cin >> q;
    
    vector<int>f(MAX_N * 3, -1), value(MAX_N * 3), numberIndex(MAX_N, -1);
    
    for(int i = 0; i < MAX_N; i++) {
        numberIndex[i] = i + MAX_N;
        value[i + MAX_N] = i;
    }
    int freeIndex = 2 * MAX_N, size = 0;
    while(q--) {
        int t; cin >> t;
        if(t == 1) {
            int x; cin >> x;
            f[size] = numberIndex[x];
            size++;
        } else {
            int x, y; cin >> x >> y;
            if(x != y) {
                f[numberIndex[x]] = numberIndex[y];
                value[freeIndex] = x;
                numberIndex[x] = freeIndex;
                freeIndex++;
            }
            
        }
    }
    
    for(int i = 0; i < size; i++) {
        cout << value[Find(i, f)] << ' ';
    }
    cout << '\n';
    
    
    return 0;
}
