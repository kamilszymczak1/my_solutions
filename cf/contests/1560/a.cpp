#include <iostream>

using namespace std;

void TestCase() {
    int k; cin >> k;
    int i = 0, goodCnt = 0;
    while(goodCnt < k) {
        i++;
        if(i % 3 != 0 && i % 10 != 3)
            goodCnt++;
    }
    cout << i << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}

