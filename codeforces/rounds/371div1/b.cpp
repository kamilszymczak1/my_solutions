#include <cstdio>
#include <algorithm>

using namespace std;

bool swapped_dimensions = false;

int query(int x1, int y1, int x2, int y2) {
    if(swapped_dimensions) {
        int _x1 = x1, _y1 = y1, _x2 = x2, _y2 = y2;
        x1 = _y1;
        y1 = _x1;
        x2 = _y2;
        y2 = _x2;
    }
    printf("? %d %d %d %d\n", y1, x1, y2, x2);
    fflush(stdout);
    int x; scanf("%d", &x);
    return x;
}

void answer(int x11, int y11, int x12, int y12, int x21, int y21, int x22, int y22) {
    if(swapped_dimensions) {
        int _x11 = x11, _y11 = y11, _x12 = x12, _y12 = y12, _x21 = x21, _y21 = y21, _x22 = x22, _y22 = y22;
        x11 = _y11;
        y11 = _x11;
        x12 = _y12;
        y12 = _x12;
        
        x21 = _y21;
        y21 = _x21;
        x22 = _y22;
        y22 = _x22;
    }
    printf("! %d %d %d %d %d %d %d %d\n", y11, x11, y12, x12, y21, x21, y22, x22);
    fflush(stdout);
    exit(0);
}

pair<int, int> find_y_bound(int x1, int x2, int n) {
    int max_y = 0, min_y = n + 1;
    for(int bit = 15; bit >= 0; bit--) {
        max_y += 1 << bit;
        if(max_y >= n || query(x1, 1, x2, max_y) > 0)
            max_y -= 1 << bit;
        min_y -= 1 << bit;
        if(min_y <= 1 || query(x1, min_y, x2, n) > 0)
            min_y += 1 << bit;
    }
    max_y++;
    min_y--;
    return make_pair(min_y, max_y);
}

void get(int n) {
    int max_x = 0, min_x = n + 1;
    for(int bit = 15; bit >= 0; bit--) {
        max_x += 1 << bit;
        if(max_x >= n || query(1, 1, max_x, n) == 2)
            max_x -= 1 << bit;
        
        min_x -= 1 << bit;
        if(min_x <= 1 || query(min_x, 1, n, n) == 2)
            min_x += 1 << bit;
    }
    min_x--;
    max_x++;
    
    //we have the x interval of [min_x, max_x]
    
    int left_x = min_x - 1, right_x = max_x + 1;
    for(int bit = 15; bit >= 0; bit--) {
        left_x += 1 << bit;
        if(left_x >= max_x || query(1, 1, left_x, n) > 0)
            left_x -= 1 << bit;
        
        right_x -= 1 << bit;
        if(right_x <= min_x || query(right_x, 1, n, n) > 0)
            right_x += 1 << bit;
    }
    left_x++;
    right_x--;
    
    if(left_x < right_x) {
        auto [y11, y12] = find_y_bound(min_x, left_x, n);
        auto [y21, y22] = find_y_bound(right_x, max_x, n);
        answer(min_x, y11, left_x, y12, right_x, y21, max_x, y22);
    }
}

int main() {
    int n; scanf("%d", &n);
    
    for(int i = 0; i < 2; i++) {
        get(n);
        swapped_dimensions = !swapped_dimensions;
    }
    
    return 0;
}
