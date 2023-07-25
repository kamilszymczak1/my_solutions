#include <cstdio>
#include <vector>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<int>a(n), b(n), where_in_b(n);
    for(int &x : a) {
        scanf("%d", &x); x--;
    }
    for(int i = 0; i < n; i++) {
        scanf("%d", &b[i]); b[i]--;
        where_in_b[b[i]] = i;
    }
    
    vector<bool>visited(n, false);
    int single_count = 0, non_single_count = 0;
    for(int i = 0; i < n; i++) { 
        if(visited[i])
            continue;
        
        int count = 0;
        for(int j = i; !visited[j]; j = where_in_b[a[j]]) {
            count++;
            visited[j] = true;
        }
        
        if(count % 2 == 1) {
            count--;
            single_count++;
        }
        non_single_count += count;
    }
    non_single_count /= 2;
    
    long long result = 2ll * (single_count + non_single_count) * non_single_count;
    printf("%lld\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
