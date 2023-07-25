#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--) {
        vector<int>v(3);
        cin >> v[0] >> v[1] >> v[2];
        sort(v.begin(), v.end());
        int result = 1 << 30;
        do {
            int a = v[0];
            int b = min(v[1], v[2]);
            int c = max(v[1], v[2]);
            int s = b;
            while((((c - b - 2 * s) % 3) != 0) && s > 0) {
                s--;
            }
            c -= s;
            b -= s;
            a += 2 * s;
            int currentResult = s;
            if((c - b) % 3 == 0) {
                int k = (c - b) / 3;
                if(k <= a) {
                    result = min(result, currentResult + c);
                } else {
                    int A = a;
                    b += 2 * A;
                    c -= a;
                    a = 0;
                    currentResult += A;
                    int k = (c - b) / 3;
                    if(k % 2 == 0) {
                        int op = k / 2;
                        currentResult += op * 3;
                        c -= 3 * op;
                        b += 3 * op;
                        result = min(result, c + currentResult);
                    } else {
                        int op = k / 2;
                        currentResult += op * 3 + 2;
                        c -= 3 * op;
                        b += 3 * op;
                        c -= 1;
                        b += 2;
                        result = min(result, c + currentResult);
                    }
                }
            }
        } while(next_permutation(v.begin(), v.end()));
        
        if(result == (1 << 30)) {
            cout << "-1\n";
        } else {
            cout << result << '\n';
        }
    }
    

    
    return 0;
}
