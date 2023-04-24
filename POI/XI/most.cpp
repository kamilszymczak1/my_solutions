#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    int n, a, b, last = -1, result = 0;
    cin >> n;
    if(n == 1) {
        cin >> result;
        cout << result << '\n';
        return 0;
    }
    cin >> a >> b;
    if(n % 2 == 1) {
        cin >> last;
        result += a + last;
        n--;
    }
    for(int i = 1; i < n / 2; i++) {
        int c, d; cin >> c >> d;
        result += min(2 * a + c + d, a + 2 * b + d);
    }
    result += b;
    
    cout << result << '\n';
    
    return 0;
}
