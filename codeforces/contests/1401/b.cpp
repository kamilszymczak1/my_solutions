#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    int t, zeros[2], ones[2], twos[2];
    cin >> t;
    for(int i = 0; i < t; i++) {
        for(int j = 0; j < 2; j++)
            cin >> zeros[j] >> ones[j] >> twos[j];
        int result = 0, taken;
        
        //min of 2's in a and 1's in b
        taken = min(twos[0], ones[1]);
        twos[0] -= taken;
        ones[1] -= taken;
        result += taken * 2;
        
        //min of 0's in a and 2's in b
        taken = min(zeros[0], twos[1]);
        zeros[0] -= taken;
        twos[1] -= taken;
        
        taken = min(twos[0], twos[1]);
        twos[0] -= taken;
        twos[1] -= taken;
        
        taken = min(ones[0], twos[1]);
        ones[0] -= taken;
        twos[1] -= taken;
        result -= taken * 2;
        
        cout << result << "\n";
        
    }
    
    return 0;
}
