#include <cstdio>

#define MAX_N 1000000

using namespace std;

int arr[MAX_N];

int begIndex[MAX_N * 2 + 1];
int endIndex[MAX_N * 2 + 1];

void FindAllCases(int a, int b);

int main() {
    int n, m, val;
    char c;
    scanf("%d %d\n", &n, &m);
    
    int a = - 1;
    int b = - 1;
    
    for(int i = 0; i < n; i++) {
        c = getchar();
        if(c == 'T')
            arr[i] = 2;
        else {
            arr[i] = 1;
            if(a == -1)
                a = b = i;
            else
                b = i;
        }   
    }
    
    FindAllCases(0, n - 1);
    
    if(a != -1)
        if(a + 1 < n - b)
            FindAllCases(a + 1, n - 1);
        else
            FindAllCases(0, b - 1);
    
    for(int i = 0; i < m; i++) {
        scanf("%d", &val);
        if(begIndex[val] == 0)
            printf("NIE\n");
        else
            printf("%d %d\n", begIndex[val], endIndex[val]);
    }
    
    return 0;
}

void FindAllCases(int a, int b) {
    int sum = 0;
    for(int i = a; i <= b; i++)
        sum += arr[i];
    
    while(a <= b) {
        begIndex[sum] = a + 1;
        endIndex[sum] = b + 1;
        
        if(arr[a] == 2)
            sum -= arr[a++];
        else if(arr[b] == 2)
            sum -= arr[b--];
        else
            sum -= arr[a++], sum -= arr[b--];
    }
}
