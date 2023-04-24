#include <iostream>
#include <cmath>

using namespace std;

long long FitBest(long long len, long long a, long long b, long long total) {
    if(len + b - a > total)
        return -1;
    return min(max(0ll, len - a), max(0ll, b - total + len));
}

void TestCase() {
    long long W, H; cin >> W >> H;
    long long x1, x2, y1, y2, w, h;
    cin >> x1 >> y1 >> x2 >> y2 >> w >> h;
    long long a = FitBest(w, x1, x2, W);
    long long b = FitBest(h, y1, y2, H);
    if(a == -1 && b == -1) {
        cout << "-1\n";
    } else {
        if(a == -1) {
            cout << b << '\n';
        } else if(b == -1) {
            cout << a << '\n';
        } else {
            cout << min(a, b) << '\n';
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
