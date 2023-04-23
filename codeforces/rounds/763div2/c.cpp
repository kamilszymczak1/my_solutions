#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool Check(vector<long long>&h, long long bound) {
    int n = h.size();
  //  cout << "Check for " << bound << '\n';
    vector<long long>newH(h.begin(), h.end());
    for(int i = n - 1; i >= 2; i--) {
        long long freeToMove = max(0ll, newH[i] - bound);
        long long toMove = freeToMove - (freeToMove % 3);
        if(freeToMove % 3 == 0)
            toMove = freeToMove;
        if(toMove > h[i]) {
            toMove = h[i] - (h[i] % 3);
            if(h[i] % 3 == 0)
                toMove = h[i];
        }
        newH[i - 1] += toMove / 3;
        newH[i - 2] += (toMove * 2) / 3;
        newH[i] -= toMove;
    }
    for(int i = 0; i < n; i++) {
        if(newH[i] < bound) {
   //         cout << "False\n";
            return false;
        }
    }
 //   cout << "True\n";
    return true;
}

void TestCase() {
    int n; cin >> n;
    
    vector<long long>h(n);
    for(auto &x : h)
        cin >> x;
    long long result = 0;
    for(int i = 30; i >= 0; i--) {
        if(Check(h, result + (1 << i)))
            result += (1 << i);
    }
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
