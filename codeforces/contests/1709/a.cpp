#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <queue>
#include <stack>
#include <cstring>
#include <cmath>

using namespace std;

void TestCase() {
    vector<int>keys(1);
    scanf("%d", &keys[0]);
    keys[0]--;
    vector<int>a(3);
    for(auto &y : a) {
        scanf("%d", &y);
        y--;
    }
    
    bool answer = true;
    for(int i = 0; i < 3; i++) {
        if(i >= keys.size() || keys[i] == -1) {
            answer = false;
            break;
        } else {
            keys.push_back(a[keys[i]]);
        }
    }
    printf("%s\n", answer ? "YES" : "NO");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
