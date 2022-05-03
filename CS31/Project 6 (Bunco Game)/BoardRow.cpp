//
//  BoardRow.cpp
//  Bunco
//
//  Created by Howard Stahl on 1/27/17.
//  Copyright © 2017 Howard Stahl. All rights reserved.
//

#include "BoardRow.h"


namespace cs31
{
    BoardRow::BoardRow() : mHumanWinner( false ),
                           mComputerWinner( false ),
                           mRound( 0 ),
                           mCurrentRound( false )
    {

    }

    void BoardRow::setHumanAsWinner()
    {
        mHumanWinner = true;
    }
    
    void BoardRow::setComputerAsWinner()
    {
        mComputerWinner = true;
    }
    
    void BoardRow::setRound( int round )
    {
        mRound = round;
    }
    
    void BoardRow::setCurrentRound( bool b )
    {
        mCurrentRound = b;
    }
    
    bool BoardRow::didComputerWin( ) const
    {
        return( mComputerWinner );
    }
    
    bool BoardRow::didHumanWin( ) const
    {
        return( mHumanWinner );
    }

    // in stringifying this row, -----> is used to mark the current
    // row in play and X is used to mark the winner of the round
    std::string BoardRow::display() const
    {
        std::string s = "";
        if (mCurrentRound)
        {
            s = s + "--->";
        }
        s = s + "\t";
        if (mHumanWinner)
        {
            s = s + "X\t";
        }
        else
        {
            s = s + "\t";
        }
        s = s + "\t";
        char c = mRound + '0';
        s = s + c + "\t";
        if (mComputerWinner)
        {
            s = s + "X\t";
        }
        else
        {
            s = s + "\t";
        }
        return( s );
    }
    
}