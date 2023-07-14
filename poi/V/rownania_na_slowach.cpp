#include <iostream>
#include <vector>

#define GetVal(c) c == '1' || c == '0' ? c - '0' : c - 'a' + 2

using namespace std;

void PrintPower(int base, int exponent);
void DFS(int n, vector<int>*v, bool *visited);
int Query();

int main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        int exponent = Query();
        if(exponent == -1)
            cout << "0\n";
        else
            PrintPower(2, exponent);
    }
    
    return 0;
}

void DFS(int n, vector<int>*graph, bool *visited) {
    visited[n] = true;
    for(int x : graph[n])
        if(!visited[x])
            DFS(x, graph, visited);
}

int Query() {
    int k, totalSize = 0, leftSize, rightSize, *positions, *size, result = -1;
    cin >> k;
    k += 2;
    positions = new int[k];
    size = new int[k];
    positions[0] = 0;
    positions[1] = 1;
    size[0] = size[1] = 1;
    if(k > 2) {
        cin >> size[2];
        totalSize = size[2];
        positions[2] = 2;
        for(int i = 3; i < k; i++) {
            cin >> size[i];
            positions[i] = positions[i - 1] + size[i - 1];
            totalSize += size[i];
        }
    }
    
    string s[2];
    cin >> leftSize >> s[0] >> rightSize >> s[1];
    
    int leftLength = 0, rightLength = 0;
    
    for(int i = 0; i < leftSize; i++)
        leftLength += size[GetVal(s[0][i])];
    
    for(int i = 0; i < rightSize; i++)
        rightLength += size[GetVal(s[1][i])];
    
    if(leftLength != rightLength)
        return -1;
    
    char c[2] = {'1', '1'};
    int pos[2] = {1, 1}, index[2] = {-1, -1};
    
    vector<int>*graph = new vector<int>[totalSize + 2];
    bool *visited = new bool[totalSize + 2];
    fill(visited, visited + totalSize + 2, false);
    
    for(int k = 0; k < leftLength; k++) {
        for(int i = 0; i < 2; i++) {
            if(pos[i] >= size[GetVal(c[i])]) {
                pos[i] = 0;
                c[i] = s[i][++index[i]];
            }
        }
        int a = positions[GetVal(c[0])] + pos[0];
        int b = positions[GetVal(c[1])] + pos[1];
        graph[a].push_back(b);
        graph[b].push_back(a);
        
        for(int i = 0; i < 2; i++)
            pos[i]++;
    }
    
    DFS(0, graph, visited);
    if(visited[1])
        return -1;
    
    for(int i = 1; i < totalSize + 2; i++)
        if(!visited[i]) {
            result++;
            DFS(i, graph, visited);
        }
    
    delete[] visited;
    delete[] graph;
    delete[] positions;
    delete[] size;
    
    return result;
}

//this function can print any power of any number

void PrintPower(int base, int exponent) {
    vector<int>number(1, 1), additional(1, 0);
    
    for(int k = 0; k < exponent; k++) {
        for(unsigned i = 0; i < number.size(); i++) {
            number[i] = (number[i] * base) + additional[i];
            additional[i] = 0;
            if(number[i] > 9 && i == number.size() - 1) {
                number.push_back(0);
                additional.push_back(number[i] / 10);
            } else if(i < number.size() - 1)
                additional[i + 1] = number[i] / 10;
            number[i] %= 10;
        }
    }
    
    for(int i = number.size() - 1; i >= 0; i--)
        cout << number[i];
    cout << "\n";
}
