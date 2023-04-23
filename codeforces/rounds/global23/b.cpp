#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <cmath>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<int>ones, zeroes;
    for(int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        if(x == 0)
            zeroes.push_back(i);
        else
            ones.push_back(i);
    }
    
    if(ones.empty() || zeroes.empty()) {
        printf("0\n");
        return;
    }
    
    reverse(ones.begin(), ones.end());
    
    int result = 0;
    while(!zeroes.empty() && !ones.empty()) {
        int x = zeroes.back();
        int y = ones.back();
        
        if(x < y)
            break;
        result++;
        zeroes.pop_back();
        ones.pop_back();
    }
    
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
