#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n; cin >> n;
    if(n == 0) {
        cout << "0\n";
        return 0;
    }
    
    vector<int>digits;
    while(n > 0) {
        digits.push_back(n % 10);
        n /= 10;
    }
    
    reverse(digits.begin(), digits.end());
    
    for(int i = 3; i < (int)digits.size(); i++)
        digits[i] = 0;
    
    for(int x : digits)
        cout << x;
    cout << '\n';
    
    return 0;
}
