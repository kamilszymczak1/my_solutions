#include <iostream>
#include <vector>
#include <map>

using namespace std;

bool Check(vector<int>a, int k, int m) {
    const int n = a.size();
    int wrongPositions = 0;
    vector<int>newA(a.size(), 0);
    for(int i = 0; i < n; i++)
        newA[(i - k + n) % n] = a[i];
    swap(a, newA);
    vector<int>positionAtA(n);
    for(int i = 0; i < n; i++)
        positionAtA[a[i]] = i;
    
    int swaps = 0;
    for(int i = 0; i < n; i++) {
        if(positionAtA[i] != i) {
            int posOfI = positionAtA[i];
            positionAtA[i] = i;
            positionAtA[a[i]] = posOfI;
            swap(a[i], a[posOfI]);
            swaps++;
        }
    }
    return swaps <= m;
}

void TestCase() {
    int n, m; cin >> n >> m;
    vector<int>onGoodPosition(n, 0);
    vector<int>a(n), cnt(2 * n + 1, 0);
    for(int i = 0; i < n; i++) {
        cin >> a[i]; a[i]--;
        onGoodPosition[(i - a[i] + n) % n]++;
    }
    
    vector<int>ans;
    for(int k = 0; k < n; k++) {
        int wrong = n - onGoodPosition[k];
        int minimumRequiredMoves = wrong / 2;
        
        if(minimumRequiredMoves <= m && Check(a, k, m)) {
            ans.push_back(k);
        }
    }
    cout << ans.size() << ' ';
    for(int x : ans)
        cout << x << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
