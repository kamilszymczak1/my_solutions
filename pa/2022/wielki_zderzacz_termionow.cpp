#include <cstdio>
#include <algorithm>

#warning change the size of arrays

using namespace std;

const long long mod = 1'000'000'007;

const int MAX_N = 300'000;
char c[MAX_N];

int n, q;
const int leaf_count = 1 << 18;

int tree[leaf_count * 2][3];
int cnt[256][2];

void merge_sons(int x) {
    fill(tree[x], tree[x] + 3, 0);
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            tree[x][(i + j) % 3] += 1ll * tree[x * 2][i] * tree[x * 2 + 1][j] % mod;
            if(tree[x][(i + j) % 3] >= mod)
                tree[x][(i + j) % 3] -= mod;
        }
    }
}

void build_tree() {
    for(int i = 0; i < n; i++)
        cnt[c[i]][i % 2]++;
    for(int i = 0; i < leaf_count * 2; i++)
        fill(tree[i], tree[i] + 3, 0);
    for(int i = leaf_count; i < leaf_count + n; i++) {
        switch(c[i - leaf_count]) {
            case 'C': tree[i][1] = 1; break;
            case 'Z': tree[i][2] = 1; break;
            case 'N': tree[i][1] = tree[i][2] = 1; break;
        }
    }
    for(int i = n + leaf_count; i < leaf_count * 2; i++)
        tree[i][0] = 1;
    for(int i = leaf_count - 1; i > 0; i--)
        merge_sons(i);
}

void update(int x, char t) {
    cnt[c[x]][x % 2]--;
    c[x] = t;
    cnt[c[x]][x % 2]++;
    x += leaf_count;
    fill(tree[x], tree[x] + 3, 0);
    switch(t) {
        case 'C': tree[x][1] = 1; break;
        case 'Z': tree[x][2] = 1; break;
        case 'N': tree[x][1] = tree[x][2] = 1; break;
    }
    for(x /= 2; x; x /= 2)
        merge_sons(x);
}

int get_answer() {
    if(n == 1) {
        if(c[0] == 'N')
            return 2;
        return 1;
    }
    int answer = tree[1][1] + tree[1][2];
    if(answer >= mod)
        answer -= mod;
    if(n % 2 == 1) {
        for(int j = 0; j < 2; j++)
            if(cnt['C'][j ^ 0] == 0 && cnt['Z'][j ^ 1] == 0)
                answer -= 1;
        if(answer < 0)
            answer += mod;
    }
    return answer;
}

int main() {
    scanf("%d%d", &n, &q);
    scanf("%s", c);
    build_tree();
    printf("%d\n", get_answer());
    while(q--) {
        int x; scanf("%d", &x);
        char t; scanf(" %c", &t);
        update(x - 1, t);
        printf("%d\n", get_answer());
    }
    
    return 0;
}
