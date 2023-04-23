#include <iostream>
#include <set>
#include <cassert>

using namespace std;

const int MAX_N = 1000;

int answer[MAX_N], n, k;
int seq[MAX_N][MAX_N], where_in_seq[MAX_N][MAX_N], dummy[MAX_N], dummy2[MAX_N];

const long long mod = 1'000'000'007;

long long b = 7;
long long b_pow[MAX_N];
long long seq_hash[MAX_N][MAX_N];

long long sum(int i, int l, int r) {
    long long left = seq_hash[i][r];
    long long right = seq_hash[i][l - 1];
    if(right < left)
        return right - left + mod;
    return right - left;
}

void go(int l, int r, int parent) {
    
    if(l == r) {
        answer[seq[1][l]] = parent;
        return;
    }
        
    for(int i = l + 1; i <= r - 1; i++) {
        int my_guy = seq[1][i];
        
        long long x = sum(1, l, where_in_seq[1][my_guy] - 1);
        long long y = sum(1, where_in_seq[1][my_guy] + 1, r);
        
        long long h = min(x, y) * mod + max(x, y);
        
        bool ok = true;
        for(int j = 2; j <= k; j++) {
            long long new_x = sum(j, l, where_in_seq[j][my_guy] - 1);
            long long new_y = sum(j, where_in_seq[j][my_guy] + 1, r);
            long long new_h = min(new_x, new_y) * mod + max(new_x, new_y);
            if(h != new_h)
                ok = false;
        }
        
        if(ok) {
            
            int left_guy = seq[1][l];
            for(int j = 2; j <= k; j++) {
                
                bool found_in_left = false;
                for(int t = l; t < where_in_seq[j][my_guy]; t++) {
                    if(seq[j][t] == left_guy) {
                        found_in_left = true;
                    }
                }
                
                if(!found_in_left) {
                    for(int t = l; t < where_in_seq[j][my_guy]; t++) {
                        dummy[t - l] = seq[j][t];
                    }
                    for(int t = where_in_seq[j][my_guy] + 1; t <= r; t++) {
                        dummy2[t - where_in_seq[j][my_guy] - 1] = seq[j][t];
                    }
                    
                    int ind = l;
                    for(int t = 0; t < r - where_in_seq[j][my_guy]; t++) {
                        seq[j][ind++] = dummy2[t];
                    }
                        
                    seq[j][ind++] = my_guy;
                    for(int t = 0; t < where_in_seq[j][my_guy] - l; t++) {
                        seq[j][ind++] = dummy[t];
                    }
                }
                
            }
            
            for(int j = 1; j <= k; j++) {
                for(int t = l; t <= r; t++) {
                    where_in_seq[j][seq[j][t]] = t;
                    seq_hash[j][t] = seq_hash[j][t - 1] + b_pow[seq[j][t]];
                    if(seq_hash[j][t] >= mod)
                        seq_hash[j][t] -= mod;
                }
            }
            
            answer[my_guy] = parent;
            go(l, where_in_seq[1][my_guy] - 1, my_guy);
            go(where_in_seq[1][my_guy] + 1, r, my_guy);
            
            
            return;
        }
    }
    assert(false);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> k;
    b_pow[0] = 1;
    for(int j = 1; j <= n; j++) {
        b_pow[j] = b_pow[j - 1] * b % mod;
    }
    for(int i = 1; i <= k; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> seq[i][j];
            where_in_seq[i][seq[i][j]] = j;
            seq_hash[i][j] = seq_hash[i][j - 1] + b_pow[seq[i][j]];
            if(seq_hash[i][j] >= mod)
                seq_hash[i][j] -= mod;
        }
    }
    go(1, n, -1);
    for(int i = 1; i <= n; i++)
        cout << answer[i] << ' ';
    cout << '\n';
    return 0;
}
