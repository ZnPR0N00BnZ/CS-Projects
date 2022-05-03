
#include <queue>
#include <iostream>
using namespace std;

class Coord
        {
          public:
            Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
            int r() const { return m_row; }
            int c() const { return m_col; }
          private:
            int m_row;
            int m_col;
        };

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
    queue <Coord> iqueue;
    iqueue.push(Coord(sr, sc));
    maze[sr][sc] = 'f';
    while (iqueue.empty() == false) {
        Coord current = iqueue.front();
        iqueue.pop();
        
        int curR = current.r();
        int curC = current.c();
        
        if (curR == er && curC == ec) {
            return true;
        }
        
        //Check NSEW
        if (maze[curR][curC -1] == '.') {
            iqueue.push(Coord(curR,curC-1));
            maze[curR][curC -1] = 'f';
        }
        if (maze[curR][curC +1] == '.') {
            iqueue.push(Coord(curR,curC+1));
            maze[curR][curC +1] = 'f';
        }
        if (maze[curR-1][curC] == '.') {
            iqueue.push(Coord(curR-1,curC));
            maze[curR-1][curC] = 'f';
        }
        if (maze[curR+1][curC] == '.') {
            iqueue.push(Coord(curR+1,curC));
            maze[curR+1][curC] = 'f';
        }

    }
    return false;
}


int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','X','.','.','.','X','.','.','X' },
        { 'X','.','X','.','X','X','X','X','.','X' },
        { 'X','.','X','.','.','X','.','X','.','X' },
        { 'X','.','X','X','.','X','.','.','.','X' },
        { 'X','.','.','.','.','.','.','X','X','X' },
        { 'X','.','X','X','X','X','.','X','.','X' },
        { 'X','.','.','.','.','X','X','X','.','X' },
        { 'X','.','X','.','.','X','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };

    if (pathExists(maze, 5,6, 8,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}

