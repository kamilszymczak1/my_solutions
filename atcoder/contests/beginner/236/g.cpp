#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

struct Matrix {
    vector<vector<int>>v;
    Matrix(int size) {
        v.resize(size, vector<int>(size, 1 << 30));
    }
};

Matrix operator* (Matrix &a, Matrix &b) {
    Matrix res(a.v.size());
    for(int i = 0; i < a.v.size(); i++) {
        for(int j = 0; j < a.v.size(); j++) {
            for(int k = 0; k < a.v.size(); k++) {
                res.v[i][j] = min(res.v[i][j], max(a.v[i][k], b.v[k][j]));
            }
        }
    }
    return res;
}

Matrix MatrixPow(Matrix M, int exp) {
    Matrix res(M.v.size());
    for(int i = 0; i < M.v.size(); i++)
        res.v[i][i] = -(1 << 30);
    for(; exp > 0; exp /= 2) {
        if(exp % 2 == 1)
            res = res * M;
        M = M * M;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, t, l; cin >> n >> t >> l;
    Matrix M(n);
    for(int i = 1; i <= t; i++) {
        int a, b; cin >> a >> b;
        M.v[a - 1][b - 1] = i;
    }
    
    M = MatrixPow(M, l);
    for(int i = 0; i < n; i++) {
        cout << ((M.v[0][i] == (1 << 30)) ? -1 : M.v[0][i]) << ' ';
    cout << '\n';
    
    return 0;
}
