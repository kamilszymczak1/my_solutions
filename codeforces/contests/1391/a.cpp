#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    int t, n;
    cin >> t;
    for(int i = 0; i < t; i++) {
        cin >> n;
        for(int j = 1; j <= n; j++)
            cout << j << " ";
        cout << "\n";
    }
    
    return 0;
}
