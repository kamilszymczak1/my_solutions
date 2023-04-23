#include <algorithm>
#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

class Solution {
public:
    int maxStudents(vector<vector<char>>& seats) {
        int height = seats.size(), width = seats[0].size();
        vector<int>dp(1 << height, 0), goodMask(1 << height, 0);
        for(int i = 0; i < (1 << height); i++) {
            for(int j = 0; j < height; j++)
                goodMask[i] |= ((1 << j) & i) ? (1 << max(0, j - 1)) | (1 << j) | (1 << min(height - 1, j + 1)) : 0;
            goodMask[i] ^= (1 << height) - 1;
        }
        int chairs, prevChairs = 0;
        for(int i = 0; i < width; i++) {
            chairs = 0;
            for(int j = 0; j < height; j++)
                chairs |= (int)(seats[j][i] == '.') << j;
            vector<int>newDp(1 << height, 0);
            for(int prevMask = prevChairs; ; prevMask = (prevMask - 1) & prevChairs) {
                for(int currentMask = goodMask[prevMask] & chairs; ; currentMask = (currentMask - 1) & goodMask[prevMask] & chairs) {
                    newDp[currentMask] = max(newDp[currentMask], dp[prevMask] + __builtin_popcount(currentMask));
                    if(currentMask == 0)
                        break;
                }
                if(prevMask == 0)
                    break;
            }
            swap(dp, newDp);
            prevChairs = chairs;
        }
        
        return *max_element(dp.begin(), dp.end());
            
    }
};

int main() {
    vector<vector<char>>v = {{'#','.','#','#','.','#'},
                             {'.','#','#','#','#','.'},
                             {'#','.','#','#','.','#'}};
    Solution s;
    cout << s.maxStudents(v) << '\n';
    
    v = {{'.','#'},
                {'#','#'},
                {'#','.'},
                {'#','#'},
                {'.','#'}};
    cout << s.maxStudents(v) << '\n';
    v = {{'#','.','.','.','#'},
                {'.','#','.','#','.'},
                {'.','.','#','.','.'},
                {'.','#','.','#','.'},
                {'#','.','.','.','#'}};
                
    cout << s.maxStudents(v) << '\n';
    
    v = {{'.','#','#','.'},
         {'.','.','.','#'},
         {'.','.','.','.'},
         {'#','.','#','#'}};
         
    cout << s.maxStudents(v) << '\n';

    return 0;
}
