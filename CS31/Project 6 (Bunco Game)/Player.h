//
//  Player.h
//  Bunco
//
//  Created by Howard Stahl on 1/27/17.
//  Copyright © 2017 Howard Stahl. All rights reserved.
//

#ifndef Player_h
#define Player_h
#include "Die.h"

namespace cs31
{
    
    // CS 31 students have been provided this class to represent
    // one of the Bunco Players.  Each Player has its own Die, knows
    // which round is currently being played and knows how to scores
    // it rolled value for the current round.
    // CS 31 students need to complete the TODO portions of this class
    class Player
    {
    public:
        Player();
        int roll( );                 // TODO randomly toss the Player's Die
        int roll( int amount );      // TODO force a certain roll
        void setRound( int round );  // TODO set current round, resetting the Player's score
        int  getScore( ) const;      // TODO how many times has Player tossed the current round value?
    private:
        Die mDie;    // the Player's Die
        int mScore;  // the Player's score for this round
        int mRound;  // the current round value, a number between 1 and 6
    };
    
}

#endif /* Player_h */
