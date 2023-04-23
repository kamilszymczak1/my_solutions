#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int Calc(int ones, int twos, int num) {
    if(num <= ones + twos * 2) {
        if(num % 2 == 1 && ones == 0) {
            if(num == 1)
                return 1 << 30;
            return 1;
        }
        return 0;
    }
    if(ones > 0 && (ones + twos * 2 - 1) % 3 == num % 3)
        return (num - ones - twos * 2 + 1) / 3;
    if((ones > 1 || twos > 0) && (ones + twos * 2 - 2) % 3 == num % 3)
        return (num - ones - twos * 2 + 2) / 3;
    if((ones + twos * 2) % 3 == num % 3)
        return (num - ones - twos * 2) / 3;
    if(num % 3 == 0)
        return num / 3;
    return 1 << 30;
}

void TestCase() {
    int n; cin >> n;
    vector<int>v(n);
    for(int &x : v)
        cin >> x;
    int result = 1 << 30;
    
    for(int ones = 0; ones <= 3; ones++) {
        for(int twos = 0; twos <= 3; twos++) {
            int threes = 0;
            for(int i = 0; i < n; i++) {
                threes = max(threes, Calc(ones, twos, v[i]));
            }
            result = min(result, ones + twos + threes);
        }
    }
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
