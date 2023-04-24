#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 256;

struct Matrix {
    bool v[MAX_N][MAX_N];
    Matrix() {}
    Matrix(int _n) {
        for(int i = 0; i < _n; i++) {
            fill(v[i], v[i] + _n, 0);
        }
    }
};
int n, m, k;
vector<int>initialPoints;
Matrix M[30];

Matrix operator* (Matrix &a, Matrix &b) {
    Matrix result(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                result.v[i][j] = result.v[i][j] || (a.v[i][k] && b.v[k][j]);
                if(result.v[i][j])
                    break;
            }
        }
    }
    return result;
}

bool PossibleMeet(Matrix &t) {
    for(int i = 0; i < n; i++) {
        bool wrong = false;
        for(int x : initialPoints) {
            wrong |= !t.v[x][i];
        }
        if(!wrong)
            return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> m >> k;
    for(int i = 0; i < k; i++) {
        int a; cin >> a;
        initialPoints.push_back(a - 1);
    }
    sort(initialPoints.begin(), initialPoints.end());
    if(initialPoints[0] == initialPoints.back()) {
        cout << "TAK\n0\n";
        return 0;
    }
    M[0] = Matrix(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        M[0].v[a - 1][b - 1] = true;
    }
    
    int p;
    for(p = 1; (1 << p) <= n * n * n; p++) {
        M[p] = M[p - 1] * M[p - 1];
    }
    
    if(!PossibleMeet(M[p - 1])) {
        cout << "NIE\n";
        return 0;
    }
   
    int beg = 0;
    Matrix currentM = Matrix(n);
    for(int i = 0; i < n; i++)
        currentM.v[i][i] = true;
    
    for(int len = p - 1; len >= 0; len--) {
        Matrix newM = currentM * M[len];
        if(!PossibleMeet(newM)) {
            beg += 1 << len;
            currentM = newM;
        }
    }
    
    cout << "TAK\n" << beg + 1 << '\n';
    
    return 0;
}
