#include <cstdio>
#include <vector>

using namespace std;

int query(int x, int y) {
    printf("? %d %d\n", x + 1, y + 1);
    fflush(stdout);
    char c = 0;
    while(c != '<' && c != '=' && c != '>')
        scanf("%c", &c);
    if(c == '<')
        return -1;
    if(c == '=')
        return 0;
    return 1;
}

void test_case() {
    int n; scanf("%d", &n);
    vector<int>lo, hi;
    for(int i = 0; i < n / 2; i++) {
        if(query(i * 2, i * 2 + 1) == -1) {
            lo.push_back(i * 2);
            hi.push_back(i * 2 + 1);
        } else {
            hi.push_back(i * 2);
            lo.push_back(i * 2 + 1);
        }
    }
    
    if(n == 1) {
        printf("! 1 1\n");
        fflush(stdout);
        return;
    }
    
    int best_lo = n % 2 ? n - 1 : lo[0];
    int best_hi = n % 2 ? n - 1 : hi[0];
    for(int i = 1 - n % 2; i < (int)lo.size(); i++) {
        if(query(best_lo, lo[i]) == 1) {
            best_lo = lo[i];
        }
    }
    
    for(int i = 1 - n % 2; i < (int)hi.size(); i++) {
        if(query(best_hi, hi[i]) == -1) {
            best_hi = hi[i];
        }
    }
    
    printf("! %d %d\n", best_lo + 1, best_hi + 1);
    fflush(stdout);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
