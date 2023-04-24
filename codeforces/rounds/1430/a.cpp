#include <iostream>
#include <array>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    int t, n;
    cin >> t;
    
    array<int, 3>res;
    
    for(int i = 0; i < t; i++) {
        cin >> n;
        array<int, 3>res = {0, 0, 0};
        if((n % 3 == 1 && n < 7) || (n % 3 == 2 && n < 5)) {
            cout << "-1\n";
            continue;
        }
        if(n % 3 == 0)
            res[0] = n / 3;
        if(n % 3 == 1)
            res[0] = (n - 7) / 3, res[2] = 1;
        if(n % 3 == 2)
            res[0] = (n - 5) / 3, res[1] = 1;
        
        for(int x : res)
            cout << x << " ";
        cout << "\n";
    }
    
    return 0;
}
