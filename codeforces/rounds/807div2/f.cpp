#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <string>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_N = 1007;

int n, guessed, leafCount;
bool ans[MAX_N], det[MAX_N];
int order[MAX_N];

bool stop = false;

int Ask() {
    for(int i = 0; i < n; i++)
        putchar(ans[i] ? 'T' : 'F');
    putchar('\n');
    fflush(stdout);
    int k; scanf("%d", &k);
    return k;
}

int Try(int a, int b, int lo, int hi) {
    
    if(a >= b || stop)
        return 0;
    
    for(int i = a; i < b; i++)
        ans[order[i]] = 1;
    
    int myGuessed = Ask();
    
    for(int i = a; i < b; i++)
        ans[order[i]] = 0;
    
    if(myGuessed == n) {
        stop = true;
        return 0;
    }
    
    int range = b - a;
    int difference = myGuessed - guessed;
    if(difference == range) {
        for(int i = a; i < b; i++)
            det[order[i]] = 1;
        return range;
    }
    
    if(difference == -range) {
        for(int i = a; i < b; i++)
            det[order[i]] = 0;
        return 0;
    }
    
    int oneCount = (difference + range) / 2;
    
    
    const int mid = (lo + hi) / 2;
    int L = Try(a, min(b, mid), lo, mid);
    
    if(L == oneCount || stop)
        return oneCount;
    int R = Try(max(a, mid), b, mid, hi);
    return L + R;
}

int main() {
    srand(time(NULL));
    scanf("%d", &n);
    guessed = Ask();
    
    if(guessed == n)
        return 0;
    
    for(int i = 0; i < n; i++)
        order[i] = i;
    
    for(int i = 0; i < n; i++)
        swap(order[n - i - 1], order[rand() % (n - i)]);
    
    leafCount = 1;
    while(leafCount < n)
        leafCount *= 2;
    
    Try(0, n, 0, leafCount);
    
    for(int i = 0; i < n; i++)
        printf("%c", det[i] ? 'T' : 'F');
    printf("\n");
    fflush(stdout);
    
    return 0;
}
