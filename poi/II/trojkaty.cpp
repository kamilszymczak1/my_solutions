#include <algorithm>
#include <vector>
#include <cstdio>
#include <cctype>

using namespace std;

int NextInt() {
    int c, result = 0;
    do {
        c = getchar_unlocked();
    } while(!isdigit(c));
    do {
        result = result * 10 + c - '0';
        c = getchar_unlocked();
    } while(isdigit(c));
    return result;
}

int main() {
    vector<int>a(1, NextInt());
    while(a.back() != 0)
        a.push_back(NextInt());
    a.pop_back();
    sort(a.begin(), a.end());
    const int n = a.size();
    for(int i = 0; i < n - 2; i++) {
        if(a[i] + a[i + 1] > a[i + 2]) {
            printf("%d %d %d\n", a[i], a[i + 1], a[i + 2]);
            return 0;
        }
    }
    printf("NIE\n");
    return 0;
}
