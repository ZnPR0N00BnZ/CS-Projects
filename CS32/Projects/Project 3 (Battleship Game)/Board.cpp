#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>

using namespace std;

class BoardImpl
{
  public:
    //Create Board with g referencing the game being placed in
    //You can receive info about board size using this object
    BoardImpl(const Game& g);
    
    //Clears the board, removes all ships
    void clear();
    
    //Block (nRows*nCols/2) positions on board
    //Can use game object's random position function here
    //Once a square is blocked, player cannot place a ship there
    //Only MediocrePlayer uses this
    void block();
    
    //Unblocks all positions, only used by MediocrePlayer
    void unblock();
    
    //Place ship onto board, returns true if successful
    //pg 7 specs list of things to check for
    bool placeShip(Point topOrLeft, int shipId, Direction dir);
    
    //Removeship using id,returns if it succeeds or not
    //pg 8 specs list of things to check for
    bool unplaceShip(Point topOrLeft, int shipId, Direction dir);
    
    //Displays board using format defined on pg8-9
    void display(bool shotsOnly) const;
    
    //Attacks a point on other player's board
    //Returns if attk is valid (valid point on board)
    //Parameters:
    //-shotHit passed by ref and set to true if it was a hit
    //-shipDestroyed set to true if ship destroyed
    //-If ship was destroyed, set shipID to destroyed ship
    bool attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId);
    
    //Returns if all ships destroyed
    bool allShipsDestroyed() const;

  private:
      // TODO:  Decide what private members you need.  Here's one that's likely
      //        to be useful:
    const Game& m_game;
    char grid[MAXROWS][MAXCOLS];
};

BoardImpl::BoardImpl(const Game& g)
 : m_game(g)
{
    for (int r = 0; r < m_game.rows(); r++) {
        for (int c = 0; c< m_game.cols(); c++) {
            grid[r][c] = '.';
        }
    }
}

void BoardImpl::clear()
{
    for (int r = 0; r < m_game.rows(); r++) {
        for (int c = 0; c< m_game.rows(); c++) {
            if (isalpha(grid[r][c])) {
                grid[r][c] = '.';
            }
        }
    }
}

void BoardImpl::block()
{
    int blocked = 0;
    int totalblocks = m_game.rows() * m_game.cols();
    while (blocked < totalblocks/2) {
        int ranR = randInt(m_game.rows());
        int ranC = randInt(m_game.cols());
            
        char toBlock = grid[ranR][ranC];
        if (toBlock == '.') {
            grid[ranR][ranC] = '#';
            blocked++;
        }
        else if (toBlock == '#') {}
    }
}

void BoardImpl::unblock()
{
    for (int r = 0; r < m_game.rows(); r++)
        for (int c = 0; c < m_game.cols(); c++)
        {
            if (grid[r][c] == '#') {
                grid[r][c] = '.';
            }
        }
}

bool BoardImpl::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    //Conditions
    //1.ShipID invalid
    //2.Ship partly/fully outside board
    //3.Ship overlap already placed ship
    //4.Ship overlap one or more blocked positions
    //5.ShipID already being used, that ship has not yet been unplaced since
    //NOTE: If function returns false, board must be unchanged
    
    //Checks condition 1
    if (shipId < 0 || shipId > m_game.nShips()-1) {
        return false;
    }
    
    //Checks condition 2
    if (dir == HORIZONTAL) {
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            Point tester(topOrLeft.r,topOrLeft.c+i);
            if (!m_game.isValid(tester)) {
                return false;
            }
        }
    }
    if (dir == VERTICAL) {
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            Point tester(topOrLeft.r+i,topOrLeft.c);
            if (!m_game.isValid(tester)) {
                return false;
            }
        }
    }
    
    //Checks condition 3 HOW TO DO????
    if (dir == HORIZONTAL) {
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            for (int j = 0; j<m_game.nShips(); j++) {
                if (grid[topOrLeft.r][topOrLeft.c+i] == m_game.shipSymbol(j)) {
                    return false;
                }
            }
        }
    }
    if (dir == VERTICAL) {
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            for (int j = 0; j<m_game.nShips(); j++) {
                if (grid[topOrLeft.r+i][topOrLeft.c] == m_game.shipSymbol(j)) {
                    return false;
                }
            }
        }
    }

    
    //Checks condition 4
    if (dir == HORIZONTAL) {
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            if (grid[topOrLeft.r][topOrLeft.c+i] == '#') {
                return false;
            }
        }
    }
    if (dir == VERTICAL) {
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            if (grid[topOrLeft.r+i][topOrLeft.c] == '#') {
                return false;
            }
        }
    }
    
    //Checks condition 5
    for (int r = 0; r < m_game.rows(); r++) {
        for (int c = 0; c < m_game.cols(); c++) {
            if (grid[r][c] == m_game.shipSymbol(shipId)) {
                return false;
            }
        }
    }
    
    //Pass all tests, proceed
    if (dir == HORIZONTAL) {
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            grid[topOrLeft.r][topOrLeft.c+i] = m_game.shipSymbol(shipId);
        }
    }
    if (dir == VERTICAL) {
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            grid[topOrLeft.r+i][topOrLeft.c] = m_game.shipSymbol(shipId);
        }
    }
    
    return true;
}

bool BoardImpl::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    //Conditions:
    //1.shipId is invalid
    //2. Board does not contain entire ship at indicated locations.
    
    //Checks condition 1
    if (shipId < 0 || shipId > m_game.nShips()-1) {
        return false;
    }
    
    //Checks condition 2
    if (dir == HORIZONTAL) {
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            if (grid[topOrLeft.r][topOrLeft.c+i] != m_game.shipSymbol(shipId)) {
                return false;
            }
        }
    }
    if (dir == VERTICAL) {
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            if (grid[topOrLeft.r+i][topOrLeft.c] != m_game.shipSymbol(shipId)) {
                return false;
            }
        }
    }
    
    //Passed all tests
    if (dir == HORIZONTAL) {
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            grid[topOrLeft.r][topOrLeft.c+i] = '.';
        }
    }
    if (dir == VERTICAL) {
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            grid[topOrLeft.r+i][topOrLeft.c] = '.';
        }
    }
    
    return true;
}

void BoardImpl::display(bool shotsOnly) const
{
    //top numbers
    cout<< "  ";
    for (int i = 0; i < m_game.cols(); i++) {
        cout << i;
    }
    cout << endl;
    
    if (shotsOnly == false) {
    for (int r = 0; r < m_game.rows(); r++) {
        cout << r << " ";
        for (int c=0; c < m_game.cols(); c++) {
            cout << grid[r][c];
        }
        cout<<endl;
    }
    }
    else if (shotsOnly == true) {
        for (int r = 0; r < m_game.rows(); r++) {
            cout << r << " ";
            for (int c=0; c < m_game.cols(); c++) {
                if (grid[r][c] != 'X' && grid[r][c] != 'o' && grid[r][c] != 'o') {
                cout << '.';
            }
                else {
                    cout << grid[r][c];
                }

            }             cout<<endl;
        }
    }
}

bool BoardImpl::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    //for now just set all parameters to false in its specific case
    char charAtPoint = grid[p.r][p.c];
    //int tempshipId = shipId;
    if (!m_game.isValid(p)) {
        shotHit = false;
        shipDestroyed = false;
        shipId = -1;
        return false;
    }
    else if (charAtPoint == 'X' || charAtPoint == 'o') {
        shotHit = false; //optional?
        shipDestroyed = false;
        shipId = -1;
        return false;
    }
    
    //Hits a ship segment
    if (charAtPoint != 'o' && charAtPoint != 'X' && charAtPoint != '.') {
        grid[p.r][p.c] = 'X';
        shotHit = true;
    }
    //Missed
    else if (charAtPoint == '.') {
        shotHit = false;
        shipDestroyed = false;
        shipId = -1;
        grid[p.r][p.c] = 'o';
    }
    //to get shipID
    for (int i = 0; i<m_game.nShips(); i++) {
        if (m_game.shipSymbol(i) == charAtPoint) {
            shipId = i;
            break;
        }
    }
    
    //shipDestroyed and shipID parameters
    //checking if remaining of board has that character. If yes, change 2 parameters accordingly
    //shipId is now i;
    shipDestroyed = true;
    for (int r = 0; r < m_game.rows(); r++) {
        for (int c = 0; c < m_game.cols(); c++) {
            
            if (grid[r][c] == charAtPoint) {
                //if found a char of that ship left, change parameters and never enter this loop again
                shipDestroyed = false;
                shipId = -1;
                return true;
            }
        }
    }
    
    return true;
     
}

bool BoardImpl::allShipsDestroyed() const
{
    //trying out new solution
    
    for (int i=0; i< m_game.rows(); i++) {
        for (int j=0; j< m_game.cols(); j++) {
            if (grid[i][j] != 'X' && grid[i][j] != 'o' && grid[i][j] != '.') {
                return false;
            }
        }
        
    }
    return true;

}

//******************** Board functions ********************************

// These functions simply delegate to BoardImpl's functions.
// You probably don't want to change any of this code.

Board::Board(const Game& g)
{
    m_impl = new BoardImpl(g);
}

Board::~Board()
{
    delete m_impl;
}

void Board::clear()
{
    m_impl->clear();
}

void Board::block()
{
    return m_impl->block();
}

void Board::unblock()
{
    return m_impl->unblock();
}

bool Board::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->placeShip(topOrLeft, shipId, dir);
}

bool Board::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->unplaceShip(topOrLeft, shipId, dir);
}

void Board::display(bool shotsOnly) const
{
    m_impl->display(shotsOnly);
}

bool Board::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    return m_impl->attack(p, shotHit, shipDestroyed, shipId);
}

bool Board::allShipsDestroyed() const
{
    return m_impl->allShipsDestroyed();
}
