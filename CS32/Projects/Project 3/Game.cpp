#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>

using namespace std;

class ship
{
public:
    ship(int len, char symbol, string name)
    {
        m_len = len;
        m_symbol = symbol;
        m_name = name;
    }
    int getLen() const { return m_len; }
    char getSymbol() const { return m_symbol; }
    string getName() const { return m_name; }

private:
    int m_len;
    char m_symbol;
    string m_name;
};

class GameImpl
{
public:
    // Creates game object with nRows and nCols, cannot exceed MAXROW MAXCOL in globals.h
    GameImpl(int nRows, int nCols);

    // Returns nRows and nCols
    int rows() const;
    int cols() const;

    // Returns if p is valid
    bool isValid(Point p) const;

    // Returns random point
    Point randomPoint() const;

    // Adds ship to board if possible and returns boolean if added
    // eg g.addShip(5, 'A', "Aircraft Carrier")
    bool addShip(int length, char symbol, string name);

    // Returns no. of valid ships added
    int nShips() const;

    // Legnth of ship given its ID
    int shipLength(int shipId) const;

    // Returns char representing ship w that ID
    char shipSymbol(int shipId) const;

    // Returns shipName given that ID
    string shipName(int shipId) const;

    // Runs game returning pointer to winning player...or nullptr if game fails to play
    // Actions:
    //     -Create board object for each Player
    //     -Calls placeship for each player...return nullptr instantly if fails
    //     -Start game
    //     -On each round:
    //        -Maybe display other player's board (deoending on if other player is human or not)
    //        -Execute first players attack
    //        -Display result of attack
    //        -Switch turn
    //     -If losing player is human, display winner
    Player *play(Player *p1, Player *p2, Board &b1, Board &b2, bool shouldPause);

private:
    int m_r;
    int m_c;
    int m_nships;
    vector<ship> shipvector;
    vector<int> humanPtsAttacked;
};

void waitForEnter()
{
    cout << "Press enter to continue: ";
    cin.ignore(10000, '\n');
}

GameImpl::GameImpl(int nRows, int nCols) : m_nships(0)
{
    m_r = nRows;
    m_c = nCols;
}

int GameImpl::rows() const
{
    return m_r;
}

int GameImpl::cols() const
{
    return m_c;
}

bool GameImpl::isValid(Point p) const
{
    return p.r >= 0 && p.r < rows() && p.c >= 0 && p.c < cols();
}

Point GameImpl::randomPoint() const
{
    return Point(randInt(rows()), randInt(cols()));
}

bool GameImpl::addShip(int length, char symbol, string name)
{
    // check conditions
    // 1. length of positive number and must allow ship to fit on board
    // 2. symbol must be a printable char other than X, o and . , must not be same as other ship

    // 1. Invalid length
    if (length <= 0)
    {
        return false;
    }
    // 2. Length  bigger than BOTH row and col
    if (length > rows() && length > cols())
    {
        return false;
    }
    // 3. Symbol is X, o or .
    if (symbol == 'X' || symbol == 'o' || symbol == '.')
    {
        return false;
    }
    // 4. Symbol same as other ship's symbol
    for (int i = 0; i < m_nships; i++)
    {
        if (symbol == shipvector.at(i).getSymbol())
        {
            return false;
        }
    }
    // 5. Check its a printable character
    if (isprint(symbol) == 0)
    {
        return false;
    }
    m_nships++;
    ship Ship(length, symbol, name);
    shipvector.push_back(Ship);
    return true;
}

int GameImpl::nShips() const
{
    return m_nships;
}

int GameImpl::shipLength(int shipId) const
{
    return shipvector.at(shipId).getLen();
}

char GameImpl::shipSymbol(int shipId) const
{
    return shipvector.at(shipId).getSymbol();
}

string GameImpl::shipName(int shipId) const
{
    return shipvector.at(shipId).getName();
}

Player *GameImpl::play(Player *p1, Player *p2, Board &b1, Board &b2, bool shouldPause) // Implement if p1 is human + both human?
{

    if (p1->placeShips(b1) && p2->placeShips(b2))
    {
        bool shotHit = false;
        bool shipDestroyed = false;
        int shipId = -1;
        bool validShot = true;

        // CASE: shouldPause = false and both players are non-human
        if (p1->isHuman() == false && p2->isHuman() == false && shouldPause == false)
        {
            while (!b1.allShipsDestroyed() && !b2.allShipsDestroyed())
            {
                cout << p1->name() << "'s turn. Board for " << p2->name() << ":" << endl;
                b2.display(false);
                Point PointToAttackp1 = p1->recommendAttack();
                b2.attack(PointToAttackp1, shotHit, shipDestroyed, shipId);
                p2->recordAttackByOpponent(PointToAttackp1);
                p1->recordAttackResult(PointToAttackp1, validShot, shotHit, shipDestroyed, shipId);
                if (shotHit && !shipDestroyed)
                {
                    cout << p1->name() << " attacked "
                         << "(" << PointToAttackp1.r << "," << PointToAttackp1.c << ") and hit something, resulting in:" << endl;
                }
                else if (!shotHit)
                {
                    cout << p1->name() << " attacked "
                         << "(" << PointToAttackp1.r << "," << PointToAttackp1.c << ") and missed, resulting in:" << endl;
                }
                else if (shotHit && shipDestroyed)
                {
                    cout << p1->name() << " attacked "
                         << "(" << PointToAttackp1.r << "," << PointToAttackp1.c << ") and destroyed the " << shipName(shipId) << ", resulting in:" << endl;
                }
                b2.display(false);

                //
                if (b1.allShipsDestroyed())
                {
                    cout << p2->name() << " wins!" << endl;
                    return p2;
                }
                else if (b2.allShipsDestroyed())
                {
                    cout << p1->name() << " wins!" << endl;
                    return p1;
                }

                //
                cout << p2->name() << "'s turn. Board for " << p1->name() << ":" << endl;
                b1.display(false);
                Point PointToAttackp2 = p2->recommendAttack();
                b1.attack(PointToAttackp2, shotHit, shipDestroyed, shipId);
                p1->recordAttackByOpponent(PointToAttackp2);
                p2->recordAttackResult(PointToAttackp2, validShot, shotHit, shipDestroyed, shipId);
                if (shotHit && !shipDestroyed)
                {
                    cout << p2->name() << " attacked "
                         << "(" << PointToAttackp2.r << "," << PointToAttackp2.c << ") and hit something, resulting in:" << endl;
                }
                else if (!shotHit)
                {
                    cout << p2->name() << " attacked "
                         << "(" << PointToAttackp2.r << "," << PointToAttackp2.c << ") and missed, resulting in:" << endl;
                }
                else if (shotHit && shipDestroyed)
                {
                    cout << p2->name() << " attacked "
                         << "(" << PointToAttackp2.r << "," << PointToAttackp2.c << ") and destroyed the " << shipName(shipId) << ", resulting in:" << endl;
                }
                b1.display(false);

                //
                if (b1.allShipsDestroyed())
                {
                    cout << p2->name() << " wins!" << endl;
                    return p2;
                }
                else if (b2.allShipsDestroyed())
                {
                    cout << p1->name() << " wins!" << endl;
                    return p1;
                }
            }
        }

        // CASE: Both players non-human
        else if (p1->isHuman() == false && p2->isHuman() == false)
        {
            while (!b1.allShipsDestroyed() && !b2.allShipsDestroyed())
            {
                cout << p1->name() << "'s turn. Board for " << p2->name() << ":" << endl;

                Point PointToAttackp1 = p1->recommendAttack();
                b2.attack(PointToAttackp1, shotHit, shipDestroyed, shipId);
                p2->recordAttackByOpponent(PointToAttackp1);
                p1->recordAttackResult(PointToAttackp1, validShot, shotHit, shipDestroyed, shipId);
                if (shotHit && !shipDestroyed)
                {
                    cout << p1->name() << " attacked "
                         << "(" << PointToAttackp1.r << "," << PointToAttackp1.c << ") and hit something, resulting in:" << endl;
                }
                else if (!shotHit)
                {
                    cout << p1->name() << " attacked "
                         << "(" << PointToAttackp1.r << "," << PointToAttackp1.c << ") and missed, resulting in:" << endl;
                }
                else if (shotHit && shipDestroyed)
                {
                    cout << p1->name() << " attacked "
                         << "(" << PointToAttackp1.r << "," << PointToAttackp1.c << ") and destroyed the " << shipName(shipId) << ", resulting in:" << endl;
                }
                b2.display(false);
                cout << "Press enter to continue: ";
                string enterkey = "";
                getline(cin, enterkey);

                //
                if (b1.allShipsDestroyed())
                {
                    cout << p2->name() << " wins!" << endl;
                    return p2;
                }
                else if (b2.allShipsDestroyed())
                {
                    cout << p1->name() << " wins!" << endl;
                    return p1;
                }

                //
                cout << p2->name() << "'s turn. Board for " << p1->name() << ":" << endl;
                b1.display(false);
                Point PointToAttackp2 = p2->recommendAttack();
                b1.attack(PointToAttackp2, shotHit, shipDestroyed, shipId);
                p1->recordAttackByOpponent(PointToAttackp2);
                p2->recordAttackResult(PointToAttackp2, validShot, shotHit, shipDestroyed, shipId);
                if (shotHit && !shipDestroyed)
                {
                    cout << p2->name() << " attacked "
                         << "(" << PointToAttackp2.r << "," << PointToAttackp2.c << ") and hit something, resulting in:" << endl;
                }
                else if (!shotHit)
                {
                    cout << p2->name() << " attacked "
                         << "(" << PointToAttackp2.r << "," << PointToAttackp2.c << ") and missed, resulting in:" << endl;
                }
                else if (shotHit && shipDestroyed)
                {
                    cout << p2->name() << " attacked "
                         << "(" << PointToAttackp2.r << "," << PointToAttackp2.c << ") and destroyed the " << shipName(shipId) << ", resulting in:" << endl;
                }
                b1.display(false);

                cout << "Press enter to continue: ";
                string enterkey2 = "";
                getline(cin, enterkey2);

                //
                if (b1.allShipsDestroyed())
                {
                    cout << p2->name() << " wins!" << endl;
                    return p2;
                }
                else if (b2.allShipsDestroyed())
                {
                    cout << p1->name() << " wins!" << endl;
                    return p1;
                }
            }
        }
        // CASE: P2 IS HUMAN
        else if (p1->isHuman() == false && p2->isHuman() == true)
        {
            while (!b1.allShipsDestroyed() && !b2.allShipsDestroyed())
            {
                cout << p1->name() << "'s turn. Board for " << p2->name() << ":" << endl;
                b2.display(false);
                Point PointToAttackp1 = p1->recommendAttack();
                b2.attack(PointToAttackp1, shotHit, shipDestroyed, shipId);
                p1->recordAttackResult(PointToAttackp1, validShot, shotHit, shipDestroyed, shipId);
                if (shotHit && !shipDestroyed)
                {
                    cout << p1->name() << " attacked "
                         << "(" << PointToAttackp1.r << "," << PointToAttackp1.c << ") and hit something, resulting in:" << endl;
                }
                else if (!shotHit)
                {
                    cout << p1->name() << " attacked "
                         << "(" << PointToAttackp1.r << "," << PointToAttackp1.c << ") and missed, resulting in:" << endl;
                }
                else if (shotHit && shipDestroyed)
                {
                    cout << p1->name() << " attacked "
                         << "(" << PointToAttackp1.r << "," << PointToAttackp1.c << ") and destroyed the " << shipName(shipId) << ", resulting in:" << endl;
                }
                b2.display(false);
                cout << "Press enter to continue: ";
                string enterkey = "";
                getline(cin, enterkey);

                //
                if (b1.allShipsDestroyed())
                {
                    cout << p2->name() << " wins!" << endl;
                    return p2;
                }
                else if (b2.allShipsDestroyed())
                {
                    cout << p1->name() << " wins!" << endl;
                    cout << "Here is where " << p1->name() << "'s ships were:" << endl;
                    b1.display(false);
                    return p1;
                }

                //
                cout << p2->name() << "'s turn. Board for " << p1->name() << ":" << endl;
                b1.display(true);
                Point PointToAttackp2 = p2->recommendAttack();
                int PtToPush = PointToAttackp2.r * 10 + PointToAttackp2.c;
                b1.attack(PointToAttackp2, shotHit, shipDestroyed, shipId);
                p1->recordAttackByOpponent(PointToAttackp2);
                p2->recordAttackResult(PointToAttackp2, validShot, shotHit, shipDestroyed, shipId);
                if (shotHit && !shipDestroyed)
                {
                    humanPtsAttacked.push_back(PtToPush);
                    cout << p2->name() << " attacked "
                         << "(" << PointToAttackp2.r << "," << PointToAttackp2.c << ") and hit something, resulting in:" << endl;
                    b1.display(true);
                }
                else if (!isValid(PointToAttackp2) || find(humanPtsAttacked.begin(), humanPtsAttacked.end(), PtToPush) != humanPtsAttacked.end())
                {
                    cout << p2->name() << " wasted a shot at "
                         << "(" << PointToAttackp2.r << "," << PointToAttackp2.c << ")." << endl;
                }
                else if (!shotHit)
                {
                    humanPtsAttacked.push_back(PtToPush);
                    cout << p2->name() << " attacked "
                         << "(" << PointToAttackp2.r << "," << PointToAttackp2.c << ") and missed, resulting in:" << endl;
                    b1.display(true);
                }
                else if (shotHit && shipDestroyed)
                {
                    humanPtsAttacked.push_back(PtToPush);
                    cout << p2->name() << " attacked "
                         << "(" << PointToAttackp2.r << "," << PointToAttackp2.c << ") and destroyed the " << shipName(shipId) << ", resulting in:" << endl;
                    b1.display(true);
                }

                cout << "Press enter to continue: ";
                string enterkey2 = "";
                getline(cin, enterkey2);

                //
                if (b1.allShipsDestroyed())
                {
                    cout << p2->name() << " wins!" << endl;
                    return p2;
                }
                else if (b2.allShipsDestroyed())
                {
                    cout << p1->name() << " wins!" << endl;
                    cout << "Here is where " << p1->name() << "'s ships were:" << endl;
                    b1.display(false);
                    return p1;
                }
            }
        }
    }
    return nullptr;
}

//******************** Game functions *******************************

// These functions for the most part simply delegate to GameImpl's functions.
// You probably don't want to change any of the code from this point down.

Game::Game(int nRows, int nCols)
{
    if (nRows < 1 || nRows > MAXROWS)
    {
        cout << "Number of rows must be >= 1 and <= " << MAXROWS << endl;
        exit(1);
    }
    if (nCols < 1 || nCols > MAXCOLS)
    {
        cout << "Number of columns must be >= 1 and <= " << MAXCOLS << endl;
        exit(1);
    }
    m_impl = new GameImpl(nRows, nCols);
}

Game::~Game()
{
    delete m_impl;
}

int Game::rows() const
{
    return m_impl->rows();
}

int Game::cols() const
{
    return m_impl->cols();
}

bool Game::isValid(Point p) const
{
    return m_impl->isValid(p);
}

Point Game::randomPoint() const
{
    return m_impl->randomPoint();
}

bool Game::addShip(int length, char symbol, string name)
{
    if (length < 1)
    {
        cout << "Bad ship length " << length << "; it must be >= 1" << endl;
        return false;
    }
    if (length > rows() && length > cols())
    {
        cout << "Bad ship length " << length << "; it won't fit on the board"
             << endl;
        return false;
    }
    if (!isascii(symbol) || !isprint(symbol))
    {
        cout << "Unprintable character with decimal value " << symbol
             << " must not be used as a ship symbol" << endl;
        return false;
    }
    if (symbol == 'X' || symbol == '.' || symbol == 'o')
    {
        cout << "Character " << symbol << " must not be used as a ship symbol"
             << endl;
        return false;
    }
    int totalOfLengths = 0;
    for (int s = 0; s < nShips(); s++)
    {
        totalOfLengths += shipLength(s);
        if (shipSymbol(s) == symbol)
        {
            cout << "Ship symbol " << symbol
                 << " must not be used for more than one ship" << endl;
            return false;
        }
    }
    if (totalOfLengths + length > rows() * cols())
    {
        cout << "Board is too small to fit all ships" << endl;
        return false;
    }
    return m_impl->addShip(length, symbol, name);
}

int Game::nShips() const
{
    return m_impl->nShips();
}

int Game::shipLength(int shipId) const
{
    assert(shipId >= 0 && shipId < nShips());
    return m_impl->shipLength(shipId);
}

char Game::shipSymbol(int shipId) const
{
    assert(shipId >= 0 && shipId < nShips());
    return m_impl->shipSymbol(shipId);
}

string Game::shipName(int shipId) const
{
    assert(shipId >= 0 && shipId < nShips());
    return m_impl->shipName(shipId);
}

Player *Game::play(Player *p1, Player *p2, bool shouldPause)
{
    if (p1 == nullptr || p2 == nullptr || nShips() == 0)
        return nullptr;
    Board b1(*this);
    Board b2(*this);
    return m_impl->play(p1, p2, b1, b2, shouldPause);
}
