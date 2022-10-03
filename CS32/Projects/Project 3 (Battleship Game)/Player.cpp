#include "Player.h"
#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

//*********************************************************************
//  AwfulPlayer
//*********************************************************************

class AwfulPlayer : public Player
{
  public:
    AwfulPlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                                bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
  private:
    Point m_lastCellAttacked;
};

AwfulPlayer::AwfulPlayer(string nm, const Game& g)
 : Player(nm, g), m_lastCellAttacked(0, 0)
{}

bool AwfulPlayer::placeShips(Board& b)
{
      // Clustering ships is bad strategy
    for (int k = 0; k < game().nShips(); k++)
        if ( ! b.placeShip(Point(k,0), k, HORIZONTAL))
            return false;
    return true;
}

Point AwfulPlayer::recommendAttack()
{
    if (m_lastCellAttacked.c > 0)
        m_lastCellAttacked.c--;
    else
    {
        m_lastCellAttacked.c = game().cols() - 1;
        if (m_lastCellAttacked.r > 0)
            m_lastCellAttacked.r--;
        else
            m_lastCellAttacked.r = game().rows() - 1;
    }
    return m_lastCellAttacked;
}

void AwfulPlayer::recordAttackResult(Point /* p */, bool /* validShot */,
                                     bool /* shotHit */, bool /* shipDestroyed */,
                                     int /* shipId */)
{
      // AwfulPlayer completely ignores the result of any attack
}

void AwfulPlayer::recordAttackByOpponent(Point /* p */)
{
      // AwfulPlayer completely ignores what the opponent does
}

//***********************HELPER FUNCTIONS***************************
string removeSpacingAfter(string withspace) {
    //starting is space
    if(withspace.at(0) == ' ') {
        return withspace;
    }
    else if (withspace.at(0) =='v') {
        return "v";
    }

    
    else if (withspace.at(0) == 'h') {
        return "h";
    }

        return withspace;
}

//*********************************************************************
//  HumanPlayer
//*********************************************************************

bool getLineWithTwoIntegers(int& r, int& c)
{
    bool result(cin >> r >> c);
    if (!result)
        cin.clear();  // clear error state so can do more input operations
    cin.ignore(10000, '\n');
    return result;
}

// TODO:  You need to replace this with a real class declaration and
//        implementation.


class HumanPlayer : public Player
{
public:
    HumanPlayer(string nm, const Game& g);
    
    virtual ~HumanPlayer() {}
    virtual bool isHuman() const {return true; }
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                    bool shipDestroyed, int shipId) {} //not supposed to do anyt
    virtual void recordAttackByOpponent(Point p) {} //not supposed to do anyt
    
};

HumanPlayer::HumanPlayer(string nm, const Game& g): Player(nm , g) {}

bool HumanPlayer::placeShips(Board& b) {
    cout<< name() << " the Human must place " << game().nShips() << "ships." << endl;
    for (int i = 0; i < game().nShips(); i++) {
        
        //inputing h or v
        b.display(false);
        cout<<"Enter h or v for direction of " << game().shipName(i) <<" (length " <<game().shipLength(i) <<"): ";
        string input1 = "NOT H OR V";
        Direction inputDirect = VERTICAL;
        getline(cin,input1);
        string input2 = removeSpacingAfter(input1);
        if (input2 == "h") {
            inputDirect = HORIZONTAL;
        }
        else if (input2 == "v") {
            inputDirect = VERTICAL;
        }
        else {
            while (true) {
                cout<<"Direction must be h or v." <<endl;
                cout<<"Enter h or v for direction of " << game().shipName(i) <<" (length " <<game().shipLength(i) <<"): ";
                getline(cin,input1);
                string input2 = removeSpacingAfter(input1);
                if (input2 == "h") {
                    inputDirect = HORIZONTAL;
                    break;
                }
                else if (input2 == "v") {
                    inputDirect = VERTICAL;
                    break;
                }
            }
        }
        
        
        //placing ship
        while (true) {
            int r = -1; int c= -1;
            cout<< "Enter row and column of leftmost cell (e.g., 3 5): ";
            if (!getLineWithTwoIntegers(r, c)) {
                cout<<"You must enter two integers." <<endl;
            }
            else {
                Point test(r,c);
                
                if (inputDirect == HORIZONTAL) {
                    if (!b.placeShip(test, i, HORIZONTAL)) {
                        cout<<"The ship can not be placed there." << endl;
                    }
                    else {
                        break;
                    }
                }
                else if (inputDirect == VERTICAL) {
                    if (!b.placeShip(test, i, VERTICAL)) {
                        cout<<"The ship can not be placed there." << endl;
                    }
                    else {
                        break;
                    }
                }
            }
            
        }
    }
    return true; 
}
 
Point HumanPlayer::recommendAttack() {
    //need to change
    int r = -1; int c =-1;
    
    while (true) {
    cout<<"Enter the row and column to attack (e.g., 3 5): ";
    if (!getLineWithTwoIntegers(r, c)) {
        cout<<"You must enter two integers." << endl;
    }
    else {
        break;
    }

    }
    Point toAttack(r,c);
    return toAttack;
        
}

//*********************************************************************
//  MediocrePlayer
//*********************************************************************

// TODO:  You need to replace this with a real class declaration and
//        implementation.
//typedef AwfulPlayer MediocrePlayer;
// Remember that Mediocre::placeShips(Board& b) must start by calling
// b.block(), and must call b.unblock() just before returning.

class MediocrePlayer:public Player
{
public:
    MediocrePlayer(string nm, const Game& g);
    
    virtual ~MediocrePlayer() {}
    virtual bool isHuman() const {return false; }
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                    bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p) {} //supposed to do nothing
    
    //helper
    bool RecursionHelper(Board& b, int shipsLeft);
    
private:
    vector <int> totalPtsAttacked2; //trying to store points as int
    vector <int> crossPattern2;
    bool state1;
};

MediocrePlayer::MediocrePlayer(string nm, const Game& g): Player(nm , g)  {state1=true;}

bool MediocrePlayer::RecursionHelper(Board& b, int shipsLeft){
    int shipId = game().nShips() - shipsLeft;
    if (shipsLeft == 0) {
        return true;
    }
    for (int r = 0; r<game().rows(); r++) {
        for (int c = 0; c<game().cols(); c++) {
            Point p(r,c);
            if (b.placeShip(p, shipId, HORIZONTAL) && RecursionHelper(b, shipsLeft-1)) {
                return true;
            }
            else if (b.placeShip(p, shipId, VERTICAL) && RecursionHelper(b, shipsLeft-1)) {
                return true;
            }
            else if (r == game().rows() -1 && c == game().cols()-1) {
                break;
            }
        }
        if (r==game().rows()-1) {
            break;
        }
    }
    
    return false;
}


bool MediocrePlayer::placeShips(Board &b) {
    int tries = 0;
    int totalShips = game().nShips();
    while (tries < 50) {
        b.block();
        if (RecursionHelper(b, totalShips)) {
            b.unblock();
            return true;
        }
        else {
            b.unblock();
            b.clear();
            tries++;
        }
    }
    b.clear();
    b.unblock();
    
    return false;
}

Point MediocrePlayer::recommendAttack() {
    if (state1) {
        int r=randInt(game().rows()); int c = randInt(game().cols());
        Point p(r,c);
        int test = r * 10 + c;
        while (find(totalPtsAttacked2.begin(), totalPtsAttacked2.end(), test) != totalPtsAttacked2.end() ) {
            r = randInt(game().rows());
            c = randInt(game().cols());
            p.r = r;
            p.c = c;
            test = r * 10 + c;
        }
        //totalPtsAttacked2.push_back(test);
        return p;
    }
    else { //in state 2
        
        int vectorSize = 0;
        vector <int> :: iterator it;
        for (it = crossPattern2.begin(); it != crossPattern2.end(); it++) {
            vectorSize++;
        }
        
        int randomIndex = randInt(vectorSize);
        int pI = crossPattern2.at(randomIndex);
        crossPattern2.erase(crossPattern2.begin() + randomIndex);
        //totalPtsAttacked2.push_back(pI);
        if (pI < 10 && pI >= 0) {
            Point p(0, pI);
            return p;
        }
        else {
            int r = pI / 10;
            int c = pI % 10;
            Point p(r,c);
            return p;
        }
        
    }

    
}
void MediocrePlayer::recordAttackResult(Point p, bool validShot, bool shotHit,
                                bool shipDestroyed, int shipId) {
    
    //convert point to integer equivalent
    int r = p.r;
    int c = p.c;
    int test = r * 10 + c;
    
    if (!game().isValid(p) || find(totalPtsAttacked2.begin(), totalPtsAttacked2.end(), test) != totalPtsAttacked2.end()) {
        validShot = false;
        return;
    }
    
    if (!validShot) {
        shotHit = false;
        shipDestroyed = false;
        shipId = -1;
        return;
    }
     
    
    //State 1
    if (state1) {
        if (shotHit) {
            if (shipDestroyed) {
                totalPtsAttacked2.push_back(test);
            }
            else { // !shipDestroyed
                totalPtsAttacked2.push_back(test);
                state1 = false;
                for (int i=1; i<5; i++) {
                    Point Pleft(p.r,p.c-i); Point Pright(p.r,p.c+i); int PleftInt =Pleft.r* 10 + Pleft.c; int PrightInt =Pright.r* 10 + Pright.c;
                    Point Pup(p.r-i,p.c); Point Pdown(p.r+i,p.c); int PupInt =Pup.r* 10 + Pup.c; int PdownInt =Pdown.r* 10 + Pdown.c;
                    if (game().isValid(Pleft)) {
                        //int test = Pleft.r* 10 + Pleft.c;
                        crossPattern2.push_back(PleftInt);
                    }
                    if (game().isValid(Pright)) {
                        //int test = Pright.r* 10 + Pright.c;
                        crossPattern2.push_back(PrightInt);
                    }
                    if (game().isValid(Pup)) {
                        //int test = Pup.r* 10 + Pup.c;
                        crossPattern2.push_back(PupInt);
                    }
                    if (game().isValid(Pdown)) {
                        //int test = Pdown.r* 10 + Pdown.c;
                        crossPattern2.push_back(PdownInt);
                    }
                }
        }
        }
        else { // !shotHit
            int pointInt = p.r * 10 + p.c;
            totalPtsAttacked2.push_back(pointInt);

    }
        return;
    }
        
    //State 2
    else if (!state1) {
        
        
        if (!shotHit) {
            int pointInt = p.r * 10 + p.c;
            totalPtsAttacked2.push_back(pointInt);
            //crossPattern2.erase(find(crossPattern2.begin(), crossPattern2.end(), pointInt));
            crossPattern2.erase(remove(crossPattern2.begin(), crossPattern2.end(), pointInt), crossPattern2.end());
        
        }
        else if (shotHit && !shipDestroyed) {
            int pointInt = p.r * 10 + p.c;
            totalPtsAttacked2.push_back(pointInt);
            //crossPattern2.erase(find(crossPattern2.begin(), crossPattern2.end(), pointInt));
            crossPattern2.erase(remove(crossPattern2.begin(), crossPattern2.end(), pointInt), crossPattern2.end());
        }
        else if (shotHit && shipDestroyed) {
            int pointInt = p.r * 10 + p.c;
            totalPtsAttacked2.push_back(pointInt);
            state1 = true;
            //erase all entries in crossPattern
            while (!crossPattern2.empty()) {
                crossPattern2.erase(crossPattern2.begin());
            }
        }
        return;
    }

}

//*********************************************************************
//  GoodPlayer
//*********************************************************************

// TODO:  You need to replace this with a real class declaration and
//        implementation.
class GoodPlayer:public Player
{
public:
    GoodPlayer(string nm, const Game& g);
    
    virtual ~GoodPlayer() {}
    virtual bool isHuman() const {return false; }
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                    bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p) {} //supposed to do nothing
    
    //helper
    bool RecursionHelper(Board& b, int shipsLeft);
    
private:
    vector <int> totalPtsAttacked2; //trying to store points as int
    vector <int> crossPattern2;
    bool state1;
    vector <int> checkerPts; //when constructing, fill this up to be drawn from recommend attack
};

GoodPlayer:: GoodPlayer(string nm, const Game& g): Player(nm , g)  {
    state1=true;
    for (int r=0; r < game().rows(); r++) {
        for (int c = 0 ; c < game().cols(); c++) {
            if (r % 2 == 0 && c % 2 == 0) {
                
                checkerPts.push_back(r*10 + c);
            }
            else if (r % 2 == 1 && c % 2 == 1) {
                checkerPts.push_back(r*10 +c);
            }
        }
    }
}

bool GoodPlayer::RecursionHelper(Board& b, int shipsLeft){
 //
    
    
    int shipId = game().nShips() - shipsLeft;
    if (shipsLeft == 0) {
        return true;
    }
    //idea is to spread out the ships
 
    
    
    if (shipsLeft % 5 == 0) {
    for (int r = 0; r<game().rows(); r++) {
        for (int c = 0; c<game().cols(); c++) {
            Point p(r,c);
            if (b.placeShip(p, shipId, HORIZONTAL) && RecursionHelper(b, shipsLeft-1)) {
                return true;
            }
            else if (b.placeShip(p, shipId, VERTICAL) && RecursionHelper(b, shipsLeft-1)) {
                return true;
            }
            else if (r == game().rows() -1 && c == game().cols()-1) {
                break;
            }
        }
        if (r==game().rows()-1) {
            break;
        }
    }
    
    return false;
    }
    else if (shipsLeft % 4 == 0) {
        
        for (int c = game().cols()-1; c > -1; c--) {
            for (int r = 0; r < game().rows() ; r++) {
                Point p(r,c);
                if (b.placeShip(p, shipId, HORIZONTAL) && RecursionHelper(b, shipsLeft-1)) {
                    return true;
                }
                else if (b.placeShip(p, shipId, VERTICAL) && RecursionHelper(b, shipsLeft-1)) {
                    return true;
                }
                else if (r == game().rows()-1 && c == 0) {
                    break;
                }
            }
            if (c == 0) {
                break;
            }
            
        }
        return false;
    }
    else if (shipsLeft % 3 == 0) {
        
        for (int r = game().rows()-1; r > -1; r--) {
            for (int c = game().cols()-1; c > -1 ; c--) {
                Point p(r,c);
                if (b.placeShip(p, shipId, HORIZONTAL) && RecursionHelper(b, shipsLeft-1)) {
                    return true;
                }
                else if (b.placeShip(p, shipId, VERTICAL) && RecursionHelper(b, shipsLeft-1)) {
                    return true;
                }
                else if (r == 0 && c == 0) {
                    break;
                }
            }
            if (r == 0) {
                break;
            }
            
        }
        return false;
    }
    
    else if (shipsLeft % 2 == 0) {
        
        for (int c = 0; c < game().cols(); c++) {
            for (int r = game().rows()-1; r > -1 ; r--) {
                Point p(r,c);
                if (b.placeShip(p, shipId, HORIZONTAL) && RecursionHelper(b, shipsLeft-1)) {
                    return true;
                }
                else if (b.placeShip(p, shipId, VERTICAL) && RecursionHelper(b, shipsLeft-1)) {
                    return true;
                }
                else if (r == 0 && c == game().cols()-1) {
                    break;
                }
            }
            if (c == game().cols()-1) {
                break;
            }
            
        }
        return false;
    }
    else {
        for (int r = 0; r<game().rows(); r++) {
            for (int c = 0; c<game().cols(); c++) {
                Point p(r,c);
                if (b.placeShip(p, shipId, HORIZONTAL) && RecursionHelper(b, shipsLeft-1)) {
                    return true;
                }
                else if (b.placeShip(p, shipId, VERTICAL) && RecursionHelper(b, shipsLeft-1)) {
                    return true;
                }
                else if (r == game().rows() -1 && c == game().cols()-1) {
                    break;
                }
            }
            if (r==game().rows()-1) {
                break;
            }
        }
        
        return false;
    }
    
       
    return false;
}


bool GoodPlayer::placeShips(Board &b) {
    int tries = 0;
    int totalShips = game().nShips();
    while (tries < 50) {
        b.block();
        if (RecursionHelper(b, totalShips)) {
            b.unblock();
            return true;
        }
        else {
            b.unblock();
            b.clear();
            tries++;
        }
    }
    b.clear();
    b.unblock();
    return false;
}

Point GoodPlayer::recommendAttack() {
    if (state1) {
        if (!checkerPts.empty()) {

            int r=randInt(game().rows()); int c = randInt(game().cols());
            Point p(r,c);
            int test = r * 10 + c;
             
            while (find(totalPtsAttacked2.begin(), totalPtsAttacked2.end(), test) != totalPtsAttacked2.end() || find(checkerPts.begin(), checkerPts.end(), test) == checkerPts.end()) {
            

                    r = randInt(game().rows());
                    c = randInt(game().cols());
                    p.r = r;
                    p.c = c;
                    test = r * 10 + c;
                
            }
            return p;
        }
        else { //used all checkeredpts
            int r=randInt(game().rows()); int c = randInt(game().cols());
            Point p(r,c);
            int test = r * 10 + c;
             
            while (find(totalPtsAttacked2.begin(), totalPtsAttacked2.end(), test) != totalPtsAttacked2.end()) {
                

                    r = randInt(game().rows());
                    c = randInt(game().cols());
                    p.r = r;
                    p.c = c;
                    test = r * 10 + c;
                
            }
            return p;
        }
    }
    else { //in state 2
        
        int vectorSize = 0;
        vector <int> :: iterator it;
        for (it = crossPattern2.begin(); it != crossPattern2.end(); it++) {
            vectorSize++;
        }
        
        int randomIndex = randInt(vectorSize);
        int pI = crossPattern2.at(randomIndex);
        crossPattern2.erase(crossPattern2.begin() + randomIndex);
        if (pI < 10 && pI >= 0) {
            Point p(0, pI);
            return p;
        }
        else {
            int r = pI / 10;
            int c = pI % 10;
            Point p(r,c);
        
            
            return p;
        }
        
    }

    
}
void GoodPlayer::recordAttackResult(Point p, bool validShot, bool shotHit,
                                bool shipDestroyed, int shipId) {
    
    //convert point to integer equivalent
    int r = p.r;
    int c = p.c;
    int test = r * 10 + c;
    
    //if its a checkered point,delete
    if (p.r % 2 == 0 && p.c % 2 == 0) {
        checkerPts.erase(remove(checkerPts.begin(), checkerPts.end(), test), checkerPts.end());
    }
    else if (p.r % 2 == 1 && p.c % 2 == 1) {
        checkerPts.erase(remove(checkerPts.begin(), checkerPts.end(), test), checkerPts.end());
    }
    //
    
    if (!game().isValid(p) || find(totalPtsAttacked2.begin(), totalPtsAttacked2.end(), test) != totalPtsAttacked2.end()) {
        validShot = false;
        return;
    }
    
    if (!validShot) {
        shotHit = false;
        shipDestroyed = false;
        shipId = -1;
        return;
    }
     
    
    //State 1
    if (state1) {
        if (shotHit) {
            if (shipDestroyed) {
                totalPtsAttacked2.push_back(test);
            }
            else { // !shipDestroyed
                totalPtsAttacked2.push_back(test);
                state1 = false;
                for (int i=1; i<5; i++) {
                    Point Pleft(p.r,p.c-i); Point Pright(p.r,p.c+i); int PleftInt =Pleft.r* 10 + Pleft.c; int PrightInt =Pright.r* 10 + Pright.c;
                    Point Pup(p.r-i,p.c); Point Pdown(p.r+i,p.c); int PupInt =Pup.r* 10 + Pup.c; int PdownInt =Pdown.r* 10 + Pdown.c;
                    if (game().isValid(Pleft)) {
                        //int test = Pleft.r* 10 + Pleft.c;
                        crossPattern2.push_back(PleftInt);
                    }
                    if (game().isValid(Pright)) {
                        //int test = Pright.r* 10 + Pright.c;
                        crossPattern2.push_back(PrightInt);
                    }
                    if (game().isValid(Pup)) {
                        //int test = Pup.r* 10 + Pup.c;
                        crossPattern2.push_back(PupInt);
                    }
                    if (game().isValid(Pdown)) {
                        //int test = Pdown.r* 10 + Pdown.c;
                        crossPattern2.push_back(PdownInt);
                    }
                }
        }
        }
        else { // !shotHit
            int pointInt = p.r * 10 + p.c;
            totalPtsAttacked2.push_back(pointInt);

    }
        return;
    }
        
    //State 2
    else if (!state1) {
        
        
        if (!shotHit) {
            int pointInt = p.r * 10 + p.c;
            totalPtsAttacked2.push_back(pointInt);
            crossPattern2.erase(remove(crossPattern2.begin(), crossPattern2.end(), pointInt), crossPattern2.end());
        
        }
        else if (shotHit && !shipDestroyed) {
            int pointInt = p.r * 10 + p.c;
            totalPtsAttacked2.push_back(pointInt);
            crossPattern2.erase(remove(crossPattern2.begin(), crossPattern2.end(), pointInt), crossPattern2.end());
        }
        else if (shotHit && shipDestroyed) {
            int pointInt = p.r * 10 + p.c;
            totalPtsAttacked2.push_back(pointInt);
            state1 = true;
            //erase all entries in crossPattern
            while (!crossPattern2.empty()) {
                crossPattern2.erase(crossPattern2.begin());
            }
        }
        return;
    }

}
//*********************************************************************
//  createPlayer
//*********************************************************************

Player* createPlayer(string type, string nm, const Game& g)
{
    static string types[] = {
        "human", "awful", "mediocre", "good"
    };
    
    int pos;
    for (pos = 0; pos != sizeof(types)/sizeof(types[0])  &&
                                                     type != types[pos]; pos++)
        ;
    switch (pos)
    {
      case 0:  return new HumanPlayer(nm, g);
      case 1:  return new AwfulPlayer(nm, g);
      case 2:  return new MediocrePlayer(nm, g);
      case 3:  return new GoodPlayer(nm, g);
      default: return nullptr;
    }
}

