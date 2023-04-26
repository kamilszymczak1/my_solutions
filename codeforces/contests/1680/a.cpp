#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>

using namespace std;

void TestCase() {
    int l1, r1, l2, r2;
    scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
    vector<int>v(51);
    for(int i = l1; i <= r1; i++)
        v[i]++;
    for(int i = l2; i <= r2; i++)
        v[i]++;
    
    int result = l1 + l2;
    for(int i = 0; i <= 50; i++) {
        if(v[i] == 2) {
            result = min(result, i);
        }
    }
    
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
