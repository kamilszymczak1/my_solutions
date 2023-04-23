#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, a, b; cin >> n >> a >> b;
    
    if(n == 1) {
        cout << (a == b ? 1 : 0) << '\n';
        cout << a << ":" << b << '\n';
        return 0;
    }
    
    vector<int>l(n), r(n);
    if(a + b >= n) {
        
        if(a == 0) {
            for(int i = 0; i < n; i++)
                r[i] = 1;
            r[n - 1] += b - n;
        } else if(b == 0) {
            for(int i = 0; i < n; i++)
                l[i] = 1;
            l[n - 1] += a - n;
        } else if(a >= n) {
            for(int i = 0; i < n - 1; i++) {
                l[i] = 1;
                a--;
            }
            l[n - 2] += a;
            r[n - 1] = b;
        } else {
            for(int i = 0; i < a; i++)
                l[i] = 1;   
            for(int i = a; i < n; i++) {
                r[i] = 1;
                b--;
            }
            r[n - 1] += b;
        }
    } else {
        for(int i = 0; i < a; i++)
            l[i] = 1;
        for(int i = 0; i < b ; i++)
            r[n - i - 1] = 1;
    }
    
    int answer = 0;
    for(int i = 0; i < n; i++)
        answer += l[i] == r[i];
    cout << answer << '\n';
    for(int i = 0; i < n; i++) {
        cout << l[i] << ":" << r[i] << '\n';
    }
    return 0;
}
