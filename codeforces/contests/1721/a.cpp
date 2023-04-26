#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <stack>
#include <bitset>
#include <cstring>
#include <cmath>
#include <queue>

using namespace std;

char c[200];

void test_case() {
    vector<int>diff(26);
    int d = 0;
    for(int i = 0; i < 2; i++) {
        scanf("%s", c);
        for(int j = 0; j < 2; j++) {
            if(diff[c[j] - 'a'] == false) {
                d++;
            }
            diff[c[j] - 'a'] = true;
        }
    }
    
    printf("%d\n", d - 1);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}
