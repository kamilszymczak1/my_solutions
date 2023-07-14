#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int ceil(int x, int y) {
    if(x % y == 0)
        return x / y;
    return x / y + 1;
}

void TestCase() {
    int n, r, b; scanf("%d%d%d", &n, &r, &b);
    
    int groups = b + 1;
    int result = ceil(r, groups);
    
    vector<int>v;
    int sum = result;
    v.push_back(result);
    for(int i = 0; i < groups - 1; i++) {
        v.push_back(1);
        v.push_back(result);
        sum += result + 1;
    }
    int k = 0;
    while(sum > n) {
        v[k]--;
        k += 2;
        sum--;
    }
    
    for(int i = 0; i < (int)v.size(); i++) {
        for(int j = 0; j < v[i]; j++) {
            printf("%c", i % 2 == 0 ? 'R' : 'B');
        }
    }
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
