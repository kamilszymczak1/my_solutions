#include "maja.h"
#include <vector>
#include <set>

using namespace std;

int main() {
    int maxN = gramy_dalej();
    while(maxN != 0) {
        int ans = 1;
        vector<bool>prime(maxN + 1, true);
        for(long long i = 2; i <= maxN; i++) {
            if(prime[i]) {
                while(ans * i <= maxN) {
                    if(czy_podzielna_przez(ans * i)) {
                        ans *= i;
                    } else {
                        break;
                    }
                }
                for(int j = i + i; j <= maxN; j += i)
                    prime[j] = false;
            }
        }
        zgaduj(ans);
        maxN = gramy_dalej();
    }
    
    return 0;
}
