#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    int n, m, x, y; cin >> n >> m >> x >> y;
    for(int newX = x; newX <= n; newX++) {
        cout << newX << ' ' << y << '\n';
    }
    for(int newX = x - 1; newX >= 1; newX--) {
        cout << newX << ' ' << y << '\n';
    }
    int startX = 1;
    for(int newY = 1; newY <= m; newY++) {
        if(newY == y)
            continue;
        if(startX == 1) {
            for(int newX = 1; newX <= n; newX++) {
                cout << newX << ' ' << newY << '\n';
            }
            startX = n;
        } else {
            for(int newX = n; newX >= 1; newX--) {
                cout << newX << ' ' << newY << '\n';
            }
            startX = 1;
        }
    }
    
    
    
    return 0;
}
