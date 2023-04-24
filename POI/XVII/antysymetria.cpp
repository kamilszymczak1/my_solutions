#include <iostream>
#define MAX_N 500002

using namespace std;

int r[MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    int n;
    string napis;
    cin >> n >> napis;
    napis = "#" + napis + "$";
    int i = 1;
    int t = 0;
    r[0] = 0;
    while(i <= n) {
        while(i - t >= 1 && i + t + 1 <= n && napis[i - t] != napis[i + t + 1]) t++;
        r[i] = t;
        int k = 1;
        while(k <= t && r[i - k] != r[i] - k) {
            r[i + k] = min(r[i - k], r[i] - k);
            k++;
        }
        t -= k;
        t = max(0, t);
        i += k;
    }
    long long res = 0;
    for(int i = 1; i <= n; i++) res += r[i];
    cout << res << "\n";
    return 0;
}
