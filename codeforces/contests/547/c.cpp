#include <iostream>

using namespace std;

const int MAX_A = 500'001;
const int MAX_N = 200'000;

int a[MAX_N], mu[MAX_A], n, q, one_cnt = 0;
bool prime[MAX_A];
long long sum[MAX_A];

int main() {
    ios_base::sync_with_stdio(0);
    
    cin >> n >> q;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    mu[1] = 1;
    fill(prime, prime + MAX_A, true);
    prime[1] = false;
    for(int i = 2; i < MAX_A; i++) {
        if(prime[i]) {
            mu[i] = -1;
            for(int j = i + i; j < MAX_A; j += i) {
                prime[j] = false;
                mu[j] = (j / i) % i == 0 ? 0 : -mu[j / i];
            }
        }
    }
    
    long long answer = 0;
    for(int i = 0; i < q; i++) {
        int x; cin >> x;
        
        int my_value = a[x - 1];
        
        if(my_value > 0) {
            one_cnt += my_value == 1;
            
            for(int j = 1; j * j <= my_value; j++) {
                if(my_value % j == 0) {
                    
                    answer += (2 * sum[j] + 1) * mu[j];
                    sum[j]++;
                    
                    if(j * j != my_value) {
                        answer += (2 * sum[my_value / j] + 1) * mu[my_value / j];
                        sum[my_value / j]++;
                    }
                }
            }
            
        } else {
            my_value = -my_value;
            
            one_cnt -= my_value == 1;
            
            for(int j = 1; j * j <= my_value; j++) {
                if(my_value % j == 0) {
                    
                    answer += (1 - 2 * sum[j]) * mu[j];
                    sum[j]--;
                    
                    if(j * j != my_value) {
                        answer += (1 - 2 * sum[my_value / j]) * mu[my_value / j];
                        sum[my_value / j]--;
                    }
                }
            }
        }
        
        a[x - 1] *= -1;
        
        cout << (answer - one_cnt) / 2 << '\n';
    }
    
    return 0;
}
