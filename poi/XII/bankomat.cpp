#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;

bool possible[10000];
int result = 10000;

void Check(string &s, int size);
int GetNumber(int number, int pos);

int powOf10[5] = {10000, 1000, 100, 10, 1};

int main() {
    ios_base::sync_with_stdio(0);
    fill(possible, possible + 10000, true);
    
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int size;
        cin >> size;
        string s;
        cin >> s;
        Check(s, size);
    }
    
    cout << result << "\n";
    
    return 0;
}

void Check(string &s, int size) {
    
    int **nextAppear = new int*[10];
    for(int i = 0; i < 10; i++) {
        nextAppear[i] = new int[size];
        int lastAppear = -1;
        for(int j = size - 1; j >= 0; j--) {
            if(s[j] - '0' == i)
                lastAppear = j;
            nextAppear[i][j] = lastAppear;
        }
    }
    
    for(int i = 0; i < 10000; i++) {
        if(!possible[i])
            continue;
        
        int j = (s[0] - '0' == GetNumber(i, 0)) ? 0 : nextAppear[GetNumber(i, 0)][0];
        
        for(int k = 1; k < 4; k++) {
            
            int number = GetNumber(i, k);
            if(j != -1)
                j = nextAppear[number][j];
            if(j == -1) {
                possible[i] = false;
                result--;
                break;
            }
        }
    }
    
    for(int i = 0; i < 10; i++)
        delete[] nextAppear[i];
    delete[] nextAppear;
}

int GetNumber(int number, int pos) {
    return (number % powOf10[pos] - number % powOf10[pos + 1]) / powOf10[pos + 1];
}
