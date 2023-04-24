#include <iostream>
#include <vector>

#define SIZE 1000

using namespace std;

struct Point {
    int x, y;
    Point(int a, int b) {
        x = a;
        y = b;
    }
};

bool impressed[SIZE][SIZE];

bool Query();
int LoadBoard(int height, int width);
vector<Point>* LoadSealPattern(int height, int width);
bool Check(int x, int y, int h, int w);

int main() {
    ios_base::sync_with_stdio(0);
    
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
        if(Query())
            cout << "TAK\n";
        else
            cout << "NIE\n";
    
    return 0;
}

bool Query() {
    int height, width, a, b;
    cin >> height >> width >> a >> b;
    int impressedTiles = LoadBoard(height, width);
    
    vector<Point>*sealPattern = LoadSealPattern(a, b);
    
    if(impressedTiles % sealPattern -> size() != 0)
        return false;
    
    int checkedTiles = 0;
    
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            if(impressed[i][j])
                for(Point p : *sealPattern)
                    if(!Check(j + p.x, i + p.y, height, width))
                        return false;
    
    delete sealPattern;
    
    return true;
}

bool Check(int x, int y, int height, int width) {
    if(x < 0 || y < 0 || x >= width || y >= height || !impressed[y][x])
        return false;
    impressed[y][x] = false;
    return true;
}

vector<Point>* LoadSealPattern(int height, int width) {
    string s;
    int x, y;
    vector<Point>*result = new vector<Point>;
    for(int i = 0; i < height; i++) {
        cin >> s;
        for(int j = 0; j < width; j++)
            if(s[j] == 'x') {
                if(result -> size() == 0)
                    result -> push_back(Point(0, 0)), x = j, y = i;
                else
                    result -> push_back(Point(j - x, i - y));
            }
    }
    return result;
}

int LoadBoard(int height, int width) {
    string s;
    int result = 0;
    for(int i = 0; i < height; i++) {
        cin >> s;
        for(int j = 0; j < width; j++)
            if(s[j] == 'x')
                impressed[i][j] = 1, result++;
            else
                impressed[i][j] = 0;
    }
    return result;
}
