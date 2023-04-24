#include <cstdio>
#include <vector>

using namespace std;

int main() {
    int m, p, n; scanf("%d%d%d", &m, &p, &n);
    vector<vector<int>>snack(m, vector<int>(m, -1));
    for(int i = 0; i < p; i++) {
        int r, c, s; scanf("%d%d%d", &r, &c, &s); r--; c--;
        snack[r][c] = s;
    }
    
    vector<vector<int>>last_visit(m, vector<int>(m, -1));
    last_visit[0][0] = 0;
    int head_r = 0, head_c = 0, t = 0;
    vector<int>snake(1, 0);
    for(int i = 0; i < n; i++) {
        char q; scanf(" %c", &q);
        if(q == 'Z') {
            int r, c; scanf("%d%d", &r, &c); r--; c--;
            int snake_index = (int)snake.size() - 1 - t + last_visit[r][c];
            if(snake_index < 0) {
                printf("-1\n");
            } else {
                printf("%d\n", snake[snake_index]);
            }
        } else {
            int new_head_r = head_r, new_head_c = head_c;
            if(q == 'G')
                new_head_r--;
            if(q == 'D')
                new_head_r++;
            if(q == 'L')
                new_head_c--;
            if(q == 'P')
                new_head_c++;
            
            if(snack[new_head_r][new_head_c] != -1) {
                snake.push_back(snack[new_head_r][new_head_c]);
                snack[new_head_r][new_head_c] = -1;
            }
            
            last_visit[new_head_r][new_head_c] = ++t;
            head_r = new_head_r;
            head_c = new_head_c;
        }
    }
    
    return 0;
}
