#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    
    vector<pair<int, int>>x;
    for(int i = 0; i < n; i++) {
        int j = i;
        while(j < n && a[i] == a[j])
            j++;
        if(j - i > 1)
            x.emplace_back(i, j - 1);
        i = j - 1;
    }
    if(x.empty() || x.back().second - x[0].first == 1) {
        printf("0\n");
    } else {
        printf("%d\n", max(1, x.back().second - x[0].first - 2));
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
