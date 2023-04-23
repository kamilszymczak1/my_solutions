#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

char s[1'000'007];

void test_case() {
    int a, b, c, d; scanf("%d%d%d%d", &a, &b, &c, &d);
    scanf("%s", s);
    
    int n = a + b + 2 * c + 2 * d;
    
    int count[2] = {0, 0};
    for(int i = 0; i < n; i++)
        count[s[i] - 'A']++;
    
    if(a + c + d != count[0] || b + c + d != count[1]) {
        printf("NO\n");
        return;
    }
    
    vector<pair<int, int>>segments;
    //length and type
    
    int ab_count = 0, ba_count = 0;
    
    for(int i = 0; i < n - 1; i++) {
        if(s[i] == s[i + 1])
            continue;
        
        int j = i + 1;
        while(j < n && s[j] != s[j - 1])
            j++;
        
        int len = j - i;
        
        if(len % 2 == 1) {
            ab_count += (len - 1) / 2;
            segments.emplace_back(1, len);
        } else {
            if(s[i] == 'A') {
                ab_count += len / 2;
                segments.emplace_back(0, len);
            } else {
                ab_count += (len - 2) / 2;
                segments.emplace_back(len == 2 ? 3 : 2, -len);
            }
        }
        
        i = j - 1;
    }
    
    sort(segments.begin(), segments.end());
    
//     printf("segments = ");
//     for(auto [x, y] : segments) {
//         printf("(%d, %d) ", x, y);
//     }
//     printf("\n");
    
   // printf("ab_count = %d\n", ab_count);
    
    while(!segments.empty() && ba_count < d) {
        auto [type, len] = segments.back();
        segments.pop_back();
        len = abs(len);
        
       // printf("segments = (%d, %d)\n", type, len);
        
        if(type == 0) {
            ab_count -= len > 3 ? 2 : 1;
            ba_count += len > 2 ? 1 : 0;
            len -= 3;
        } else if(type == 2) {
            
            while(len > 0 && ba_count < d) {
                ab_count -= len > 2 ? 1 : 0;
                ba_count += 1;
                len -= 2;
            }
            
        } else if(type == 3) {
            ba_count++;
            len = 0;
        }
        
        if(ba_count >= d)
            break;
        
        while(len > 1 && ba_count < d) {
            len -= 2;
            ba_count++;
            ab_count--;
        }
        
       // printf("balance = (%d, %d)\n", ab_count, ba_count);
    }
    
    printf("%s\n", ba_count >= d && ab_count >= c ? "YES" : "NO");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}
