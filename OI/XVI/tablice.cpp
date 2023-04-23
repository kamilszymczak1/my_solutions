#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int inf = 2e9 + 7;

struct Row {
    vector<int>values;
    int lo;
    Row() : lo(inf) {}
};

bool operator< (const Row &a, const Row &b) {
    return a.lo < b.lo;
}

bool operator==(const Row &a, const Row &b) {
    return a.values == b.values;
}

vector<Row>LoadGrid(int n, int m) {
    vector<Row>result(n);
    for(Row &r : result) {
        r.values.resize(m);
        for(int &x : r.values)
            cin >> x;
        r.lo = *min_element(r.values.begin(), r.values.end());
    }
    return result;
}

vector<Row>RotateGrid(vector<Row>&grid) {
    int n = grid.size(), m = grid[0].values.size();
    vector<Row>result(m);
    for(int i = 0; i < m; i++) {
        result[i].values.resize(n);
        for(int j = 0; j < n; j++)
            result[i].values[j] = grid[j].values[i];
        result[i].lo = *min_element(result[i].values.begin(), result[i].values.end());
    }
    return result;
}

void TestCase() {
    int n, m; cin >> n >> m;
    vector<Row>A = LoadGrid(n, m), B = LoadGrid(n, m);
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    A = RotateGrid(A), B = RotateGrid(B);
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    cout << (A == B ? "TAK" : "NIE") << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
