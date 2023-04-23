#include <iostream>

using namespace std;
const int MAX_N = 3007;
bool fellow[MAX_N][MAX_N];
bool bad[MAX_N];
int n, m, x, y;

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        cin >> x >> y;
        fellow[x - 1][y - 1] = true;
        fellow[y - 1][x - 1] = true;
    }
    for(int i = 0; i < n; i++) {
        fellow[i][i] = true;
        for(int j = 0; j < n; j++) {
            if(!fellow[i][j] && !bad[i] && !bad[j]) {
                bad[i] = true;
                bad[j] = true;
            }
        }
    }
    int count = 0, i = 0;
    while(i < n && count < n / 3) {
        if(!bad[i]) {
            cout << i + 1 << ' ';
            count++;
        }
        i++;
    }
    cout << '\n';
    return 0;
}
