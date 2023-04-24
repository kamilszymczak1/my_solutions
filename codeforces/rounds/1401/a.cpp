#include <iostream>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    int t, n, k;
    cin >> t;
    for(int i = 0; i < t; i++) {
        cin >> n >> k;
        if(n < k)
            cout << k - n << "\n";
        else {
            if(k % 2 == n % 2)
                cout << "0\n";
            else
                cout << "1\n";
        }
    }
    
    return 0;
}
