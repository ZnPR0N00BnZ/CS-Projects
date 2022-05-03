
#include "History.h"
#include <iostream>

using namespace std;

History::History(int nRows, int nCols) {
    m_nRows= nRows;
    m_nCols= nCols;
    
    for (int x=0 ; x< m_nRows ; x++) {
        for (int y=0 ; y<m_nCols ; y++) {
            m_data[x][y] = 0;
        }
    }
}

bool History::record(int r, int c) {
    if (r < 1 || c > m_nCols || c < 1 || r > m_nRows) {
        return false;
    }
    else {
        m_data[r-1][c-1]++;
        return true;
    }
}
 
void History::display() const {
    clearScreen();
    
    for (int x=0 ; x< m_nRows ; x++) {
        for (int y=0 ; y<m_nCols ; y++) {
            if (m_data[x][y] > 0 && m_data[x][y] <26) {
                char letter = 'A' + m_data[x][y] - 1;
                cout<<letter;
            }
            else if (m_data[x][y] >=26 ) {
                cout<< "Z";
            }
            else {
                cout<< ".";
            }
        } cout << endl;
    }
    cout << endl;
}
