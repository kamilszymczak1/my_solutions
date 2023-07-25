#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    int t, n, a, currentA;
    cin >> t;
    for(int k = 0; k < t; k++) {
        cin >> n >> a;
        int result = n;
        currentA = a;
        for(int i = 1; i < n; i++) {
            cin >> a;
            if(a != currentA)
                result = 1;
        }
        cout << result << "\n";
    }
    
    return 0;
}
