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
#include <cassert>

using namespace std;

char c[100];

int ask(int l, int r) {
    printf("? %d ", r - l + 1);
    for(int i = l; i <= r; i++)
        printf("%d ", i);
    printf("\n");
    fflush(stdout);
    scanf("%s", c);
    return c[0] == 'Y';
}

bool check_range(int l, int r) {
    int mid = (l + r) / 2;
    int a = ask(l, mid);
    int b = ask(l, r);
    int c = ask(mid + 1, r);
    int x = b * 4 + a * 2 + c;
    
   // printf("x = %s\n", bitset<3>(x).to_string().c_str());
    
    if(x == 0b000 || x == 0b100 || x == 0b011)
        return false;
    return true;
}

int main() {
    int n; scanf("%d", &n);
    int l = 1, r = n;
    while(r - l > 1) {
       // printf("l = %d, r = %d\n", l, r);
        int mid = (r + l) / 2;
        if(check_range(l, mid, r)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    
  //  printf("l = %d, r = %d\n", l, r);
    
    
    printf("! %d\n", l);
    fflush(stdout);
    scanf("%s", c);
    if(c[1] == '(') {
        printf("! %d\n", l + 1);
        fflush(stdout);
    }
    return 0;
}
