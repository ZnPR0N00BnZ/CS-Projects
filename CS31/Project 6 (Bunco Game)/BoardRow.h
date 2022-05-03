//
//  BoardRow.h
//  Bunco
//
//  Created by Howard Stahl on 1/27/17.
//  Copyright © 2017 Howard Stahl. All rights reserved.
//

#ifndef BoardRow_h
#define BoardRow_h
#include <string>

namespace cs31
{
    
    // CS 31 Students have been provided this class which
    // is used to print one row in the Bunco board.  A row
    // tracks who won (the human player or the computer player)
    // with an X and uses an arrow (------>) to mark the
    // current round
    class BoardRow
    {
    public:
        BoardRow();
        
        void setHumanAsWinner();          // has the human player won?
        bool didHumanWin( ) const;
        void setComputerAsWinner();       // has the computer player won?
        bool didComputerWin( ) const;
        void setRound( int round );       // what is the round of this row?
        void setCurrentRound( bool b );   // is this round the current round in play?
    
        std::string display() const;      // stringify this row
        
    private:
        bool mHumanWinner;
        bool mComputerWinner;
        int  mRound;
        bool mCurrentRound;
    };
    
}

#endif /* BoardRow_h */
