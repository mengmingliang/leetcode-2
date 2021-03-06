#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class MyPoint {
public:
    int x;
    int y;
    MyPoint(int x, int y) : x(x), y(y) {}
};

class Solution {
public:
    void solve(vector<vector<char> > &board) {
        int rowSize = board.size(), colSize = rowSize > 0 ? board[0].size() : 0;
        if (rowSize <= 2 || colSize <= 2) return;

        vector<vector<char> > copy = vector<vector<char> >(board.begin(), board.end());
        vector<vector<bool> > visited = vector<vector<bool> >(rowSize, vector<bool>(colSize, false));
 
        --rowSize;
        --colSize;
        queue<MyPoint *> q;
        if (copy[0][0] == 'O') {
            q.push(new MyPoint(0, 0));
            visited[0][0] = true;
        }
        if (copy[0][colSize] == 'O') {
            q.push(new MyPoint(0, colSize));
            visited[0][colSize] = true;
        }
        if (copy[rowSize][0] == 'O') {
            q.push(new MyPoint(rowSize, 0));
            visited[rowSize][0] = true;
        }
        if (copy[rowSize][colSize] == 'O') {
            q.push(new MyPoint(rowSize, colSize));
            visited[rowSize][colSize] = true;
        }
        for (int i = 1; i < colSize; ++i) {
            if (copy[0][i] == 'O')
                q.push(new MyPoint(0, i));
            if (copy[rowSize][i] == 'O')
                q.push(new MyPoint(rowSize, i));
        }
        for (int i = 1; i < rowSize; ++i) {
            if (copy[i][0] == 'O')
                q.push(new MyPoint(i, 0));
            if (copy[i][colSize] == 'O')
                q.push(new MyPoint(i, colSize));
        }
        
        for (int i = 1; i < rowSize; ++i)
            for (int j = 1; j < colSize; ++j)
                board[i][j] = 'X';
        
        MyPoint *tmp;
        int dalx[] = {-1, 0, 1, 0}, daly[] = {0, 1, 0, -1};
        int x, y;
        while (!q.empty()) {
            tmp = q.front();
            q.pop();
            
            for (int i = 0; i < 4; ++i) {
                x = tmp->x + dalx[i];
                y = tmp->y + daly[i];
                if (x < 1 || y < 1 || x > rowSize || y > colSize)
                    continue;
                if (copy[x][y] == 'O' && !visited[x][y]) {
                    board[x][y] = 'O';
                    visited[x][y] = true;
                    q.push(new MyPoint(x, y));
                }                   
            }
            delete(tmp);
        }
    }
};

void out(vector<vector<char> > data) {
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[i].size(); ++j)
           cout << data[i][j];
        cout << endl;
    }
    cout << endl;
}

int main() {
    vector<vector<char> > board;
    vector<char> b1; b1.push_back('X'); b1.push_back('X'); b1.push_back('X'); b1.push_back('X');
    vector<char> b2; b2.push_back('X'); b2.push_back('O'); b2.push_back('O'); b2.push_back('X');
    vector<char> b3; b3.push_back('X'); b3.push_back('X'); b3.push_back('O'); b3.push_back('X');
    vector<char> b4; b4.push_back('X'); b4.push_back('O'); b4.push_back('X'); b4.push_back('X');
    board.push_back(b1); board.push_back(b2); board.push_back(b3); board.push_back(b4);
    out(board);

    Solution s;
    s.solve(board);
    out(board);
    return 0;
}
