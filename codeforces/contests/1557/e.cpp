#include <iostream>
#include <vector>
#include <map>

using namespace std;


struct Cell {
    int row, column;
    Cell(int _row, int _column) : row(_row), column(_column) {}
    Cell() : row(0), column(0) {}
};
Cell operator+(Cell &a, Cell &b) {
    return Cell(a.row + b.row, a.column + b.column);
}

bool ValidPosition(Cell king, Cell queen) {
    if(king.row == queen.row || king.column == queen.column)
        return false;
    if(king.row - king.column == queen.row - queen.column)
        return false;
    if(king.row + king.column == queen.row + queen.column)
        return false;
    return king.row >= 0 && king.row < 8 && king.column >= 0 && king.column < 8;
}

struct King {
    vector<Cell>availablePositions;
    map<string, Cell>moves;
    King() {
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                availablePositions.emplace_back(i, j);
            }
        }
        moves["Right"] = Cell(0, 1);
        moves["Left"] = Cell(0, -1);
        moves["Up"] = Cell(-1, 0);
        moves["Down"] = Cell(1, 0);
        moves["Down-Right"] = moves["Right"] + moves["Down"];
        moves["Down-Left"] = moves["Left"] + moves["Down"];
        moves["Up-Right"] = moves["Right"] + moves["Up"];
        moves["Up-Left"] = moves["Left"] + moves["Up"];
    }
    string GetMove(Cell queen) {
        cout << queen.row + 1 << ' ' << queen.column + 1 << '\n' << flush;
        string move; cin >> move;
        for(Cell &position : availablePositions)
            position = position + moves[move];
        vector<Cell>newAvailablePositions;
        for(Cell position : availablePositions) {
            if(ValidPosition(position, queen)) {
                newAvailablePositions.push_back(position);
            }
        }
        swap(availablePositions, newAvailablePositions);
        return move;
    }
    Cell GetPosition() {
        return availablePositions[0];
    }
};

void MoveQueen(Cell &queen, Cell &king) {
    if(queen.column < king.column - 1) {
        queen.column = king.column - 1;
    } else if(queen.column > king.column + 1) {
        queen.column = king.column + 1;
    } else if(queen.row < king.row - 1) {
        queen.row = king.row - 1;
    } else {
        queen.row = king.row + 1;
    }
}

void TestCase() {
    King king;
    Cell queen(7, 7);
    string move = king.GetMove(queen);
    while(move != "Done") {
        Cell kingPosition = king.GetPosition();
        MoveQueen(queen, kingPosition);
        move = king.GetMove(queen);
    }
}

int main() {
    
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
