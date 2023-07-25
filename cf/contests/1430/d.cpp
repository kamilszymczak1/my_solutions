#include <cstdio>
#include <vector>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    char *s = new char[n + 1];
    scanf("%s", s);
    vector<int>v;
    for(int i = 0; i < n;) {
        int j = i;
        while(j < n && s[i] == s[j])
            j++;
        v.push_back(j - i);
        i = j;
    }
    int j = 0, i = 0, result = 0;
    while(i < v.size()) {
        while(j < (int)v.size() && v[j] <= 1)
            j++;
        if(j == (int)v.size()) {
            i += 2;
        } else {
            v[j]--;
            v[i] = 0;
            i++;
        }
        result++;
    }
    printf("%d\n", result);
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
