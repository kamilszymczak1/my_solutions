#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

int _N = 34, _queries = 0;
vector<int>_knowledge;

int dajN() {
    _knowledge.resize(_N);
    _queries = 0;
    for(int i = 0; i < _N; i++)
        _knowledge[i] = rand() % (_N + 1);
    //cout << "knowledge = ";
    return _N;
}

int tura(vector<int>_difficulty) {
    _queries++;
    int _result = 0;
    for(int i = 0; i < _N; i++)
        if(_difficulty[i] <= _knowledge[i])
            _result++;
    return _result;
}

void koniec(vector<int>_answer) {
    cout << "queries = " << _queries << ' ';
    if(_answer == _knowledge) {
        cout << "OK\n";
    } else {
        cout << "WRONG\n";
    }
    if(_queries > 4 * _N)
        cout << "queries limit exceeded\n";
}

