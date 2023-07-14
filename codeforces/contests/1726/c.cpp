#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <bitset>
#include <queue>
#include <stack>

using namespace std;

char c[200'007];

void test_case() {
    int n; scanf("%d", &n);
    scanf("%s", c);
    
    vector<int>match(2 * n);
    stack<char>s;
    int answer = 1;
    s.push('C');
    
    for(int i = 0; i < 2 * n; i++) {
        if(c[i] == '(') {
            s.push(c[i]);
        } else {
            while(!s.empty() && s.top() == 'C')
                s.pop();
            s.pop();
            if(s.empty() || s.top() != 'C') {
                answer++;
            }
            s.push('C');
        }
    }
    
    printf("%d\n", answer);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}
