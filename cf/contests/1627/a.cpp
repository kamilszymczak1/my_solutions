#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n, m; cin >> n >> m;
    int r, w; cin >> r >> w; r--; w--;
    int Bcnt = 0, sameRow = false, sameColumn = false;
    bool zero = false;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(int j = 0; j < m; j++) {
            if(s[j] == 'B') {
                Bcnt++;
                if(i == r) sameRow = true;
                if(j == w) sameColumn = true;
                if(i == r && j == w)
                    zero = true;
            }
        }
    }
    if(Bcnt == 0) {
        cout << "-1\n";
    } else if(zero) {
        cout << "0\n";
    }else if(sameRow || sameColumn) {
        cout << "1\n";
    } else {
        cout << "2\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
