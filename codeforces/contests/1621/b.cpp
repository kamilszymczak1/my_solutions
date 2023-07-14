#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Interval {
    int l, r, c;
    Interval(int _l, int _r, int _c) : l(_l), r(_r), c(_c) {}
};

void TestCase() {
    int n; cin >> n;
    Interval left(-1, -1, 0), right(-1, -1, 0), leftLong(-1, -1, 0);
    cin >> left.l >> left.r >> left.c;
    right = leftLong = left;
    cout << left.c << '\n';
    for(int i = 1; i < n; i++) {
        int l, r, c; cin >> l >> r >> c;
        if(l < leftLong.l) {
            leftLong = Interval(l, r, c);
        } else if(l == leftLong.l) {
            if(leftLong.r == r) {
                leftLong.c = min(leftLong.c, c);
            } else if(leftLong.r < r) {
                leftLong = Interval(l, r, c);
            }
        }
        if(l < left.l) {
            left = Interval(l, r, c);
        } else if(l == left.l) {
            left.c = min(left.c, c);
        }
        if(r > right.r) {
            right = Interval(l, r, c);
        } else if(r == right.r) {
            right.c = min(right.c, c);
        }
        
        if(right.r - left.l > leftLong.r - leftLong.l) {
            cout << right.c + left.c << '\n';
        } else if(right.r - left.l == leftLong.r - leftLong.l) {
            cout << min(right.c + left.c, leftLong.c) << '\n';
        } else {
            cout << leftLong.c << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
