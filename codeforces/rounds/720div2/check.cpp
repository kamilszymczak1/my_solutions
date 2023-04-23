#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int v[1000];


int main()  {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }
    int k;
    cin >> k;
    for(int i = 0; i < k; i++) {
        int a, b, x, y;
        cin >> a >> b >> x >> y;
        if(min(v[a - 1], v[b - 1]) != min(x, y)) {
            cout << min(v[a - 1], v[b - 1]) << '\n';
            cout << min(x, y) << '\n';
            cout << "ERROR min at " << i << "\n";
            return 0;
        }
        v[a - 1] = x;
        v[b - 1] = y;
    }
    for(int i = 0; i < n - 1; i++) {
        if(__gcd(v[i], v[i + 1]) != 1) {
            cout << "ERROR gcd\n";
            return 0;
        }
    }
    cout << "OK\n";
}
