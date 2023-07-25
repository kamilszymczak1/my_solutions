#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int inf = 999999999;

bool superior(vector<int>&a, vector<int>&b) {
    int count = 0;
    for(int i = 0; i < 5; i++)
        if(a[i] < b[i])
            count++;
        return count >= 3;
}

bool Check(int x, vector<vector<int>>&rank) {
    for(int i = 0; i < rank.size(); i++) {
        int cnt = 0;
        for(int j = 0; j < 5; j++)
            cnt += rank[x][j] < rank[i][j];
        if(i != x && cnt <= 2)
            return false;
    }
    return true;
}

void TestCase() {
    int n; cin >> n;
    pair<int, vector<int>>best = {-1, vector<int>(5, inf)};
    vector<vector<int>>rank(n, vector<int>(5, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 5; j++)
            cin >> rank[i][j];
        if(superior(rank[i], best.second))
            best = {i, rank[i]};
    }
    
    if(Check(best.first, rank)) {
        cout << best.first + 1 << '\n';
    } else {
        cout << "-1\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
