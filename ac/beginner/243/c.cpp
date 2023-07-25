#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct X {
    int x, y;
    bool left;
    X() {}
};

bool operator<(X a, X b) {
    if(a.y == b.y)
        return a.x < b.x;
    return a.y < b.y;
}

int main() {
    int n; scanf("%d", &n);
    vector<X>v(n);
    char *s = new char[n + 1];
    for(int i = 0; i < n; i++)
        scanf("%d%d", &v[i].x, &v[i].y);
    scanf("%s", s);
    for(int i = 0; i < n; i++)
        v[i].left = s[i] == 'L';
    
    
    sort(v.begin(), v.end());
    
    bool ans = false;
    for(int i = 0; i < n;) {
        int j = i;
        bool right = false;
        while(j < n && v[i].y == v[j].y) {
            if(v[j].left && right)
                ans = true;
            if(!v[j].left)
                right = true;
            j++;
        } 
        i = j;
    }
    
    if(ans) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    
    return 0;
}
