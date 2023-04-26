#include <iostream>

#define MAX_N 100000

using namespace std;

int amount[MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    
    int t, n, hiAmount, hiAmountCount, val;
    cin >> t;
    for(int k = 0; k < t; k++) {
        cin >> n;
        hiAmount = 0;
        
        fill(amount, amount + n, 0);
        for(int i = 0; i < n; i++) {
            cin >> val;
            val--;
            amount[val]++;
            
            if(amount[val] > hiAmount) {
                hiAmountCount = 1;
                hiAmount = amount[val];
            } else if(amount[val] == hiAmount)
                hiAmountCount++;
        }
        int other = n - (hiAmount * hiAmountCount);
        int placesToFill = hiAmount - 1;
        cout << (other / placesToFill) + hiAmountCount - 1 << "\n";
    }
    
    return 0;
}
