#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
    vector<int>a(6), b(6);
    for(int &x : a)
        cin >> x;
    for(int &x : b)
        cin >> x;
    
    long double result = 0;
    for(int i = 0; i < 6; i++) {
        result += max(a[i], b[i]);
    }
    cout << fixed << setprecision(12) << result / 200.0 << '\n';
}
