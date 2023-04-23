#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    srand(time(NULL));
    int n = rand() % 3 + 4;
    vector<int>a(n);
    for(int i = 0; i < n; i++)
        a[i] = rand() % 4 + 1;
    a[rand() % n] = 0;
    cout << 1 << ' ' << n << '\n' << flush;
    while(true) {
        string mark; cin >> mark;
        if(mark == "?") {
            int x, y, z; cin >> x >> y >> z;
            cout << max({a[z - 1], a[y - 1], a[x - 1]}) - min({a[z - 1], a[y - 1], a[x - 1]}) << '\n' << flush;
        } else {
            int x, y; cin >> x >> y >> y >> y;
            if(a[x - 1] == 0 || a[y - 1] == 0) {
                cout << "OK\n";
            } else {
                cout << "WA\n";
            }
            break;
        }
    }
}
