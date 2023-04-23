#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct Ans {
    int ind, value;
    char type;
    Ans(int _ind, char _type, int _value) : ind(_ind), type(_type), value(_value) {}
};

vector<Ans>ans;

struct Grid {
    vector<int>v;
    void Load() {
        for(int i = 0; i < 6; i++) {
            string s; cin >> s;
            for(auto c : s) {
                v.push_back(c <= '9' ? c - '0' + 26 : c - 'a');
            }
        }
    }
    void Print() {
        cout << "Grid\n";
        for(int i = 0; i < 6; i++) {
            for(int j = 0; j < 6; j++) {
                cout << setw(2) << setfill(' ') << v[i * 6 + j] << ' ';
            }
            cout << '\n';
        }
    }
    void ColumnDown(int column, int amount) {
        vector<int>columnVal;
        for(int i = 0; i < 6; i++)
            columnVal.push_back(v[i * 6 + column]);
        for(int i = 0; i < 6; i++) {
            v[i * 6 + column] = columnVal[(i - amount + 6) % 6];
        }
    }
    void RowLeft(int row, int amount) {
        vector<int>rowVal;
        for(int i = 0; i < 6; i++)
            rowVal.push_back(v[row * 6 + i]);
        for(int i = 0; i < 6; i++) {
            v[row * 6 + i] = rowVal[(i + amount + 6) % 6];
        }
    }
    
    void RotateFirst(int i, int j) {
        RowLeft(i, 1);
        ColumnDown(j, 1);
        RowLeft(i, 5);
        ColumnDown(j, 5);
    }
    
    void RotateSecond(int i, int j) {
        ColumnDown(j, 1);
        RowLeft(i, 5);
        ColumnDown(j, 5);
        RowLeft(i, 1);
    }
    
    
};

int main() {
    ios_base::sync_with_stdio(0);
    
    Grid grid;
    grid.Load();
    
    for(int i = 0; true; i++) {
        grid.Print();
        cout << "insert row and column: ";
        int row, column; cin >> row >> column;
        grid.RotateSecond(row, column);
    }
    
//     for(int i = 0; i < 36; i++) {
//         pair<int, int>target = {i / 6, i % 6};
//         pair<int, int>current = grid.Find(i);
//         while(current.first != target.first) {
//             grid.SwapVertical(current.second, current.first, current.first+ 1);
//             current.first = (current.first + 1) % 6;
//         }
//         while(current.second != target.second) {
//             grid.SwapHorizontal(target.first, target.second, target.second + 1);
//             current.second = (current.second + 1) % 6;
//         }
//     }
    
    
    
    return 0;
}

/*
 abcdef
 ghijkl
 mnopqr
 stuvwx
 yz0123
 456789
 
 hbcdef
 agijkl
 mnopqr
 stuvwx
 yz0123
 456789
 
 hbcdef
 agijkl
 mnopqr
 stuvwx
 yz0123
 456789
 
 ahcdef
 bgijkl
 mnopqr
 stuvwx
 yz0123
 456789
 */
