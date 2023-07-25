#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <map>
#include <set>
#include <cstring>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>a(n), b(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for(int i = 0; i < n; i++)
        scanf("%d", &b[i]);
    
    vector<pair<int, int>>moves;
    bool change;
    do {
        change = false;
        for(int i = 1; i < n; i++) {
            if(a[i] < a[i - 1] && b[i] <= b[i - 1]) {
                change = true;
                swap(a[i], a[i - 1]);
                swap(b[i], b[i - 1]);
                moves.emplace_back(i, i + 1);
            }
            
            if(b[i] < b[i - 1] && a[i] <= a[i - 1]) {
                change = true;
                swap(a[i], a[i - 1]);
                swap(b[i], b[i - 1]);
                moves.emplace_back(i, i + 1);
            }
        }
    } while(change);
    
    bool sorted = true;
    for(int i = 1; i < n; i++) {
        if(a[i] < a[i - 1] || b[i] < b[i - 1])
            sorted = false;
    }
    
    if(sorted) {
        printf("%d\n", (int)moves.size());
        for(auto [x, y] : moves)
            printf("%d %d\n", x, y);
    } else {
        printf("-1\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
