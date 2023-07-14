#include <iostream>

using namespace std;

int n, t, k;

int ZeroesAtPrefix(int i) {
    cout << "? 1 " << i << '\n' << flush;
    int sum;
    cin >> sum;
    return i - sum;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> t;
    for(int i = 0; i < t; i++) {
        cin >> k;
        int beg = 1, end = n;
        while(beg <= end) {
            int mid = (beg + end) >> 1;
            if(ZeroesAtPrefix(mid) < k) {
                beg = mid + 1;
            } else {
                end = mid - 1;
            }
        }
        cout << "! " << beg << '\n' << flush;
    }
}
