//
//  Bunco.cpp
//  Bunco
//
//  Created by Howard Stahl on 1/27/17.
//  Copyright © 2017 Howard Stahl. All rights reserved.
//

#include "Bunco.h"
#include <iostream>

namespace cs31
{
    Bunco::Bunco() : mRound( 1 )
    {
        setRound( mRound );
    }
    
    // stringify the game by stringifying the board
    std::string Bunco::display( std::string msg ) const
    {
        using namespace std;
        std::string s = mBoard.display();
        s = s + msg;
        
        if (gameIsOver())
        {
            if (determineGameOutcome() == TIEDGAME)
            {
                s = s + "\n\t\tBunco wound up tied!\n";
            }
            else if (determineGameOutcome() == HUMANWONGAME)
            {
                s = s + "\n\t\tyou won Bunco!\n";
            }
            else
            {
                s = s + "\n\t\tyou lost Bunco!\n";
            }
        }
        return( s );
    }
    
    // set the current round of play, notifying the board and each
    // player of the current round
    void Bunco::nextRound( )
    {
        // prevent walking off the edge of the Board...
       if (mRound <= 5)
       {
          mRound = mRound + 1;
          setRound( mRound );
       }
    }


    // set the current round of play, notifying the board and each
    // player of the current round
    void Bunco::setRound( int round )
    {
        mRound = round;
        mBoard.setCurrentRound( round );
        mHuman.setRound(round);
        mComputer.setRound(round);
    }
    
    // TODO: let the human player randomly play
    // randomly roll the human player's die and return what was rolled
    int Bunco::humanPlay( )
    {

        int amountrolled = 0;
        amountrolled = mHuman.roll();
        return( amountrolled );
    }

    // TODO: let the human player cheat
    // force a specific roll amount for the human plyaer
    int Bunco::humanPlay( const Die & d )
    {

        int amountrolled = d.getValue();
        mHuman.roll(amountrolled);
        return( amountrolled );
    }
    
    // TODO: let the computer player play
    // randomly roll the computer player's die and return what was rolled
    int Bunco::computerPlay( )
    {

        int amountrolled = 0;
        amountrolled = mComputer.roll();
        return( amountrolled );
    }
    
    // TODO: let the computer player cheat
    // force a specific roll amount for the computer player
    int Bunco::computerPlay( const Die & d )
    {

        int amountrolled = d.getValue();
        mComputer.roll(amountrolled);
        return( amountrolled );
    }

    // TODO: update the Board now that a turn of play has ended
    // if appropriate, mark the Human or Computer player as the winner on the board
    void Bunco::endTurn()
    {
        if (mHuman.getScore() > mComputer.getScore()  ) {
            mBoard.markHumanAsWinner();
        }
        else if (mComputer.getScore() > mHuman.getScore()) {
            mBoard.markComputerAsWinner();
        }
        
    }

    // TODO: considering each player's score,
    //       determine the winner of this round of play
    Bunco::ROUNDOUTCOME Bunco::determineRoundOutcome( ) 
    {

        ROUNDOUTCOME result = ROUNDOUTCOME::NOTDECIDED;
        
        if (mHuman.getScore() > mComputer.getScore()) {
            result = ROUNDOUTCOME::HUMANWON;
        }
        
        else if (mComputer.getScore() > mHuman.getScore()) {
            result = ROUNDOUTCOME::COMPUTERWON;
        }
        
        if (mHuman.getScore() == mComputer.getScore()) {
            result = ROUNDOUTCOME::NOTDECIDED;
        }
        
        return( result );
    }
    
    // TODO: count up the number of won rounds by each player
    //       to determine the game's outcome
    Bunco::GAMEOUTCOME  Bunco::determineGameOutcome( ) const
    {
  
        GAMEOUTCOME result = GAMEOUTCOME::GAMENOTOVER;
        
        if ((mBoard.countUpHumanRoundWins() + mBoard.countUpComputerRoundWins()) == 6) {
        if (mBoard.countUpHumanRoundWins() > mBoard.countUpComputerRoundWins()) {
            result = GAMEOUTCOME::HUMANWONGAME;
        }
        else if (mBoard.countUpComputerRoundWins() > mBoard.countUpHumanRoundWins()) {
            result = GAMEOUTCOME::COMPUTERWONGAME;
        }
        else if (mBoard.countUpHumanRoundWins() == mBoard.countUpComputerRoundWins()) {
            result = GAMEOUTCOME::TIEDGAME;
        }
        }
        return( result );
    }
    
    // is the game over?
    bool Bunco::gameIsOver() const
    {
        GAMEOUTCOME result = determineGameOutcome();
        return( result != GAMENOTOVER );
    }

    Player Bunco::getHuman() const
    {
        return( mHuman );
    }

    Player Bunco::getComputer() const
    {
        return( mComputer );
    }

    Board  Bunco::getBoard() const
    {
        return( mBoard );
    }

}
