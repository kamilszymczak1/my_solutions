#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
constexpr int MAX_N = 100;
int arr[MAX_N][MAX_N];

bool cmp(pair<int, int>a, pair<int, int>b) {
    if((a.first + a.second) % 2 != (b.first + b.second) % 2)
        return (a.first + a.second) % 2 < (b.first + b.second) % 2;
    if(a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
}

void TestCase() {
    int n;
    cin >> n;
    if(n == 2) {
        cout << -1 << '\n';
        return;
    }
    vector<pair<int, int>>v;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            v.emplace_back(i, j);
        }
    }
    sort(v.begin(), v.end(), cmp);
    int current = 0;
    for(auto [a, b] : v)
        arr[a][b] = ++current;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}

