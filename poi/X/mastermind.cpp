#include <iostream>

using namespace std;

bool used[10];
int newSeq[9];
int seq[9][9];
int a[9];
int b[9];
int n;

void Load();
bool FindSequence(int index);
bool CheckSequence();

int main() {
    ios_base::sync_with_stdio(0);
    
    Load();
    
    for(int i = 1; i <= 9; i++) {
        used[i] = 1;
        newSeq[0] = i;
        if(FindSequence(1)) break;
        used[i] = 0;
    }
    
    for(int i = 0; i < n; i++)
        cout << newSeq[i] << " ";
    cout << "\n";
    
    return 0;
}

bool FindSequence(int index) {
    for(int i = 1; i <= 9; i++) {
        if(used[i]) continue;
        used[i] = 1;
        newSeq[index] = i;
        if(index == n - 1 && CheckSequence())
                return true;
        if(FindSequence(index + 1)) {
            used[i] = 0;
            return true;
        }
        used[i] = 0;
    }
    return false;
}

bool CheckSequence() {
    for(int i = 0; i < n; i++) {
        int A = 0;
        int B = 0;
        for(int j = 0; j < n; j++) {
            int k = 0;
            while(k < n && seq[i][k] != newSeq[j])
                k++;
            if(k == j)
                A += newSeq[j];
            else if(k < n)
                B += newSeq[j];
        }
        if(A != a[i] || B != b[i]) return false;
    }
    return true;
}

void Load() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        for(int j = 0; j < n; j++)
            cin >> seq[i][j];
    }
}
