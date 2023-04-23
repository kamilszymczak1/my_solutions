#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>
#include <set>

using namespace std;

int dig_log(int x) {
    int ans = 0;
    while(x > 0) {
        ans++;
        x /= 10;
    }
    return ans;
}

void test_case() {
    int n; scanf("%d", &n);
    multiset<int>s1, s2;
    for(int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        s1.insert(x);
    }
    
    for(int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        if(s1.find(x) != s1.end()) {
            s1.erase(s1.find(x));
        } else {
            s2.insert(x);
        }
    }
    
    int answer = 0;
    {
        multiset<int>d;
        for(int x : s1) {
            if(x >= 10) {
                d.insert(dig_log(x));
                answer++;
            } else {
                d.insert(x);
            }
        }
            
        swap(s1, d);
    }
    
    {
        multiset<int>d;
        for(int x : s2) {
            if(x >= 10) {
                int y = dig_log(x);
                answer++;
                if(s1.find(y) != s1.end()) {
                    s1.erase(s1.find(y));
                } else {
                    d.insert(y);
                }
            } else {
                int y = x;
                if(s1.find(y) != s1.end()) {
                    s1.erase(s1.find(y));
                } else {
                    d.insert(y);
                }
            }
            
        }
        swap(s2, d);
    }
    
    int one_count1 = 0;
    for(int x : s1)
        one_count1 += x == 1;
    
    int one_count2 = 0;
    for(int x : s2)
        one_count2 += x == 1;
    
    answer += (int)s1.size() + s2.size() - (one_count1 + one_count2);
    
    printf("%d\n", answer);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
