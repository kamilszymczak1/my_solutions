#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n, m; cin >> m >> n;
    vector<int>max1(m, 0), max2(m, -1);
    vector<int>bestFriend(n, 0);
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            int x; cin >> x;
            if(x >= max1[i]) {
                max2[i] = max1[i];
                max1[i] = x;
            } else if(x > max2[i]) {
                max2[i] = x;
            }
            bestFriend[j] = max(bestFriend[j], x);
        }
    }
    
    if(n - 1 >= m) {
        int result = bestFriend[0];
        for(int i = 1; i < n; i++)
            result = min(result, bestFriend[i]);
        cout << result << '\n';
    } else {
        int result = 0;
        for(int i = 0; i < m; i++)
            result = max(result, max2[i]);
        for(int i = 0; i < n; i++)
            result = min(result, bestFriend[i]);
        cout << result << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
