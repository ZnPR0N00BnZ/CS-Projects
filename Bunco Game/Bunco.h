//
//  Bunco.h
//  Bunco
//
//  Created by Howard Stahl on 1/27/17.
//  Copyright © 2017 Howard Stahl. All rights reserved.
//

#ifndef Bunco_h
#define Bunco_h
#include <string>
#include "Player.h"
#include "Board.h"
#include "Die.h"


namespace cs31
{
 
    // CS 31 students have been provided this class to represent
    // a Bunco Game.  Each Game is made up of a Board, two Players
    // and tracks the current round of play.
    // CS 31 students need to complete the TODO portions of this class
    class Bunco
    {
    public:
        Bunco();
        
        // the possible results of a round:
        // - either a player won (human or computer) or
        // - the outcome has yet to be decided yet
        enum ROUNDOUTCOME { HUMANWON, COMPUTERWON, NOTDECIDED };
        
        // the possible results of a game:
        // - either a player won (human or computer) or
        // - the game wound up tied or
        // - the game is not yet over
        enum GAMEOUTCOME { HUMANWONGAME, COMPUTERWONGAME, TIEDGAME, GAMENOTOVER };
        
        // stringify this Game by stringifying the Game's Board
        std::string display( std::string msg = "" ) const;
        // push forward round of play
        void nextRound(  );
        
        // TODO let the human player randomly toss the die, returning the value rolled
        int humanPlay( );
        // TODO for testing purposes and force a particular rolled value
        int humanPlay( const Die & d );


        // TODO let the computer player randomly toss the die, returning the value rolled
        int computerPlay( );
        // TODO for testing purposes and force a particular rolled value
        int computerPlay( const Die & d );
        // called to end a round of play, updating the board if a player has won the round
        void endTurn();

        // what is the current round's result?
        ROUNDOUTCOME determineRoundOutcome( );
        // what is the game's result?
        GAMEOUTCOME  determineGameOutcome( ) const;
        // is the game over?
        bool gameIsOver() const;
        
        // accessors
        Player getHuman() const;
        Player getComputer() const;
        Board  getBoard() const;
    private:
        Player mHuman;    // the human player
        Player mComputer; // the computer player
        int    mRound;    // the current round of play
        Board  mBoard;    // this game's board
        
        
        // set the current round of play
        void setRound( int round );
    };
    
}

#endif /* Bunco_h */
