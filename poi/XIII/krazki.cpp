#include <iostream>

#define MAX_N 300000

using namespace std;

int ring[MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    
    int n, m, val;
    cin >> n >> m;
    cin >> ring[0];
    for(int i = 1; i < n; i++) {
        cin >> ring[i];
        ring[i] = min(ring[i - 1], ring[i]);
    }
    
    int j = n;
    for(int i = 0; i < m; i++) {
        j--;
        cin >> val;
        while(j >= 0 && ring[j] < val)
            j--;
    }
    
    cout << max(0, j + 1) << "\n";
    
    return 0;
}
