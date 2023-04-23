#pragma once
#include <iostream>
#include <vector>

using namespace std;

int _n, _zeroCount = 0;
int _queries = 0, _t;
vector<int>_v;
void Init() {
    cin >> _n;
    _v.resize(_n);
    for(auto &x : _v) {
        cin >> x;
        _zeroCount += x == 0;
    }
    _t = min(10000, _zeroCount);
}

int GetN() {
    return _n;
}

int GetT() {
    return _t;
}

void Answer(int k) {
    cout << "Answer = " << k << '\n';
    int _cnt = 0;
    for(int i = 0; i < k - 1; i++) {
        if(_v[i] == 0) {
            _cnt++;
        }
    }
    if(_v[k - 1] == 0 && _cnt == 0) {
        //cout << "Answer correct!\n";
    } else {
        cout << "Wrong answer\n";
    }
    _v[k - 1] = 1;
    _t--;
    if(_t == 0) {
        cout << "exiting..., _queries = " << _queries << '\n';
    }
}

int GetQuery() {
    return 1;
}

int PrefixSum(int k) {
    _queries++;
    int _sum = 0;
    for(int i = 0; i < k; i++)
        _sum += _v[i];
    return _sum;
}
