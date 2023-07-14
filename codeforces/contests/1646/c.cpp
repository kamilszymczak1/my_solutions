#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int Gen(int ind, long long n, int cost, vector<long long>factorial) {
    if(n == 0)
        return cost;
    int result = __builtin_popcountll(n) + cost;
    for(int i = ind; i >= 0; i--) {
        if(n < factorial[i])
            continue;
        result = min(result, Gen(i - 1, n - factorial[i], cost + 1, factorial));
    }
    return result;
}

void TestCase() {
    long long n; cin >> n;
    if(n == 1) {
        cout << "1\n";
        return;
    }
    vector<long long>factorial;
    factorial.push_back(6);
    while(factorial.back() <= n)
        factorial.push_back(factorial.back() * (factorial.size() + 3));
    factorial.pop_back();
    cout << Gen(factorial.size() - 1, n, 0, factorial) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
