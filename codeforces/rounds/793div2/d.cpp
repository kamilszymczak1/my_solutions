#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <bitset>
#include <stack>

using namespace std;

char c[200007];

void TestCase() {
    int n; scanf("%d", &n);
    scanf("%s", c);
    int sum = 0;
    for(int i = 0; i < n; i++)
        sum += c[i] - '0';
    if(sum % 2 == 1 || sum == 0) {
        printf("NO\n");
        return;
    }
    vector<pair<int, int>>e;
    int r = 0, k = 0;
    while(c[k] == '0') {
        e.emplace_back(k, k + 1);
        k++;
    }
    vector<int>ones;
    if(c[k + 1] == '0') {
        e.emplace_back(0, k + 1);
        k++;
        while(c[k + 1] == '0') {
            e.emplace_back(k, k + 1);
            k++;
        }
        ones.push_back(k);
    } else {
        ones.push_back(0);
    }
    for(int i = k + 1; i < n; i++) {
        k = i;
        while(k + 1 < n && c[k + 1] == '0') {
            e.emplace_back(k, k + 1);
            k++;
        }
        ones.push_back(k);
        i = k;
    }
        
    while(!ones.empty()) {
        int x = ones.back(); ones.pop_back();
        int y = ones.back(); ones.pop_back();
        e.emplace_back(x, y);
        if(!ones.empty()) {
            int z = ones.back();
            e.emplace_back(y, z);
            ones.pop_back();
            ones.push_back(y);
        }
    }
    printf("YES\n");
    for(auto [a, b] : e)
        printf("%d %d\n", a + 1, b + 1);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
