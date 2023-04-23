#include <cstdio>
#include <vector>

using namespace std;

bool prime(int x) {
    for(int i = 2; i * i <= x; i++) {
        if(x % i == 0) {
            return false;
        }
    }
    return true;
}

bool query(int x) {
    printf("%d\n", x);
    fflush(stdout);
    char *c = new char[4];
    scanf("%s", c);
    return c[0] == 'y';
}

int main() {
    vector<int>primes;
    for(int i = 2; i <= 50; i++) {
        if(prime(i)) {
            primes.push_back(i);
        }
    }
    for(int x : {2, 3, 5, 7}) {
        if(query(x)) {
            for(int y : primes) {
                if(x * y > 100)
                    continue;
                if(query(x * y)) {
                    printf("composite\n");
                    fflush(stdout);
                    return 0;
                }
            }
            printf("prime\n");
            fflush(stdout);
        }
    }
    printf("prime\n");
    fflush(stdout);
}
