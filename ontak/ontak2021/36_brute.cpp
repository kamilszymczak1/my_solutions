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
    bool Good() {
        bool sorted = true;
        for(int i = 1; i < 36; i++)
            if(v[i - 1] > v[i])
                sorted = false;
            return sorted;
    }
};

bool Gen(Grid grid, int depth) {
    if(grid.Good())
        return true;
    if(depth == 4)
        return false;
    for(int i = 0; i < 6; i++) {
        for(int j = 1; j <= 5; j++) {
            Grid newGrid1 = grid;
            newGrid1.RowLeft(i, j);
            
            if(Gen(newGrid1, depth + 1)) {
                ans.emplace_back(i, 'L', j);
                return true;
            }
            
            Grid newGrid2 = grid;
            newGrid2.ColumnDown(i, j);
            if(Gen(newGrid2, depth + 1)) {
                ans.emplace_back(i, 'D', j);
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    
    Grid grid;
    grid.Load();
    
//     while(true) {
//         grid.Print();
//         cout << "columnDown - 1, rowLeft - 2:";
//         int decision; cin >> decision;
//         cout << "enter number of row/column:";
//         int id; cin >> id;
//         cout << "enter amount:";
//         int amount; cin >> amount;
//         if(decision == 1)
//             grid.ColumnDown(id - 1, amount);
//         if(decision == 2)
//             grid.RowLeft(id - 1, amount);
//     }
    
    if(Gen(grid, 0)) {
        reverse(ans.begin(), ans.end());
        cout << ans.size() << '\n';
        for(const Ans a : ans)
            cout << a.ind + 1 << ' ' << a.type << ' ' << a.value << '\n';
    }
    
    
    
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
