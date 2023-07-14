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
    vector<int>a(n);
    for(int &x : a)
        scanf("%d", &x);
    int m; scanf("%d", &m);
    vector<int>b(m);
    for(int &x : b)
        scanf("%d", &x);
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    
    if(a.back() >= b.back()) {
        printf("Alice\n");
    } else {
        printf("Bob\n");
    }
    if(b.back() >= a.back()) {
        printf("Bob\n");
    } else {
        printf("Alice\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
