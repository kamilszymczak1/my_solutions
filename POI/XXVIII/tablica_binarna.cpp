#include <iostream>

using namespace std;

const int MAX_N = 1007;
bool arr[MAX_N][MAX_N];

int n, m, q;

int Query(int i1, int j1, int i2, int j2);

int main() {
    ios_base::sync_with_stdio(0);
    
    cin >> n >> m >> q;
    
    int sum = 0;
    
    int i1, j1, i2, j2;
    for(int i = 0; i < q; i++) {
        cin >> i1 >> j1 >> i2 >> j2;
        sum += Query(i1 - 1, j1 - 1, i2, j2);
        cout << sum << "\n";
    }
    
    return 0;
}


int Query(int i1, int j1, int i2, int j2) {
    
    arr[i1][j1] = !arr[i1][j1];
    arr[i1][j2] = !arr[i1][j2];
    arr[i2][j1] = !arr[i2][j1];
    arr[i2][j2] = !arr[i2][j2];
    
    if(i1 == 0 && j1 == 0)
        return arr[i2][j2] ? 1 : -1;
    
    if(arr[i1][j1]) //lg nie
        if(arr[i2][j1]) //ld nie
            if(arr[i1][j2]) //pg nie
                if(arr[i2][j2]) //pd nie
                    return (i1 == 0 || j1 == 0) ? 2 : 4;
                else //pd tak
                    return (i1 == 0 || j1 == 0) ? 0 : 2; // 1 tak
            else //pg tak
                if(arr[i2][j2]) //pd nie
                    return (j1 == 0) ? 0 : 2; // 1 tak
                else //pd tak
                    return (j1 == 0) ? -2 : 0; // 2 tak
        else //ld tak
            if(arr[i1][j2]) //pg nie
                if(arr[i2][j2]) //pd nie
                    return (i1 == 0) ? 0 : 2; // 1 tak
                else //pd tak
                    return (i1 == 0) ? -2 : 0; // 2 tak
            else //pg tak
                if(arr[i2][j2]) //pd nie
                    return 0; // 2 tak
                else //pd tak
                    return -2; // 3 tak
    else //lg tak
        if(arr[i2][j1]) //ld nie
            if(arr[i1][j2]) //pg nie
                if(arr[i2][j2]) //pd nie
                    return 2; // 1 tak
                else //pd tak
                    return 0; // 2 tak
            else //pg tak
                if(arr[i2][j2]) //pd nie
                    return (i1 == 0) ? 2 : 0; // 2 tak
                else //pd tak
                    return (i1 == 0) ? 0 : -2;
        else //ld tak
            if(arr[i1][j2]) //pg nie
                if(arr[i2][j2]) //pd nie
                    return (j1 == 0) ? 2 : 0;
                else //pd tak
                    return (j1 == 0) ? 0 : -2;
            else //pg tak
                if(arr[i2][j2]) //pd nie
                    return (i1 == 0 || j1 == 0) ? 0 : -2;
                else
                    return (i1 == 0 || j1 == 0) ? -2 : -4;
}
