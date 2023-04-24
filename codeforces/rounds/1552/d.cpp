#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

bool Solve(int index, int sum, vector<int>&a, bool taken) {
    if(sum == 0 && taken)
        return true;
    if(index == a.size())
        return false;
    bool result = false;
    result |= Solve(index + 1, sum, a, taken);
    result |= Solve(index + 1, sum + a[index], a, true);
    result |= Solve(index + 1, sum - a[index], a, true);
    return result;
}

void TestCase() {
    int n; cin >> n;
    vector<int>a(n);
    for(int &x : a)
        cin >> x;
    cout << (Solve(0, 0, a, 0) ? "YES" : "NO") << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
