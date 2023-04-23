#include <iostream>
#include <vector>

using namespace std;

int Gen(int x, vector<int>&a, vector<int>&current, int k) {
    if(x == a.size())
        return current.size() < 2 ? -1 : current.size();
    bool impossible = false;
    for(int y : current)
        impossible |= (a[x] ^ y) < k;
    int result = -1;
    if(!impossible) {
        current.push_back(a[x]);
        result = max(result, Gen(x + 1, a, current, k));
        current.pop_back();
    }
    return max(result, Gen(x + 1, a, current, k));
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, k; cin >> n >> k;
    vector<int>a(n), current;
    for(auto &x : a)
        cin >> x;
    cout << Gen(0, a, current, k) << '\n';
    return 0;
}
