//
//  Board.h
//  Bunco
//
//  Created by Howard Stahl on 1/27/17.
//  Copyright © 2017 Howard Stahl. All rights reserved.
//

#ifndef Board_h
#define Board_h
#include "BoardRow.h"

namespace cs31
{

    // CS 31 students have been provided this class to represent
    // a Bunco Board.  Each Board is made up of an array of BoardRow.
    // The display( ) method is used by the Bunco game to print the
    // current state of the game.  Each Board knows the current round
    // in play.  Each Board gets told when either the human player wins
    // the round or the computer player wins the round.  Given the
    // array of BoardRow, this class can count up how many rounds each
    // player has won.
    // CS 31 students need to complete the TODO portions of this class
    class Board
    {
    public:
        Board();
        // set the current round
        void setCurrentRound( int round );
        // TODO set human as the round winner
        void markHumanAsWinner();
        // TODO set the computer as the round winner
        void markComputerAsWinner();
        // TODO how many rounds has the computer won so far?
        int countUpComputerRoundWins( ) const;
        // TODO how many rounds has the comptuer won so far?
        int countUpHumanRoundWins( ) const;
        // stringify this Board
        std::string display( ) const;
    private:
        BoardRow mBoardRow[ 7 ];  // elements 1-6, ignoring spot 0,
                                  // are used for rounds 1-6
        int      mRound;          // the current round of play
    };
    
}

#endif /* Board_h */
