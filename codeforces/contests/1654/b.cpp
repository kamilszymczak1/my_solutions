#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_N = 200'007;
char s[MAX_N];

void TestCase() {
    scanf("%s", s);
    int n = strlen(s);
    vector<int>cnt(26);
    for(int i = 0; i < n; i++)
        cnt[s[i] - 'a']++;
    for(int i = 0; i < n; i++) {
        if(cnt[s[i] - 'a'] == 1) {
            for(int j = i; j < n; j++)
                printf("%c", s[j]);
            printf("\n");
            return;
        }
        cnt[s[i] - 'a']--;
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
}
