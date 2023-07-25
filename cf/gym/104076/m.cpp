#include <iostream>
    
using namespace std;
    
void test_case() {
    int n; cin >> n;
    long long s = 0;
    long long answer = 0;
    for(int i = 0; i < n; i++) {
        long long x; cin >> x;
        long long y = x, z = s;
        long long carry = 0;
        for(int j = 0; j < 20; j++) {
            int my_value = (y % 10) + (z % 10) + carry;
            if(my_value >= 10) {
                carry = 1;
                answer++;
            } else {
                carry = 0;
            }
            y /= 10;
            z /= 10;
        }
        
        s += x;
    }
    cout << answer << '\n';
}
    
int main() {
    int n; cin >> n;
    while(n--)
        test_case();
}
