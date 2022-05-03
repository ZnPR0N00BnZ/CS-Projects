//
//  Die.cpp
//  Bunco
//
//  Created by Howard Stahl on 1/27/17.
//  Copyright © 2017 Howard Stahl. All rights reserved.
//

#include "Die.h"
#include <random>

namespace cs31
{
    
    Die::Die( int sides ) : mSides( sides ), mValue( 1 )
    {

    }
    
    // code generates a random distribution of values
    // between 1 and mSides, storing the random value in the
    // member variable mValue for later use
    void Die::roll()
    {
        std::random_device rd;
        std::mt19937 e2(rd());
        std::uniform_int_distribution<> dist(1, mSides);
        mValue = dist(e2);
    }
    
    // returns the most recent tossed value
    int  Die::getValue( ) const
    {
        return( mValue );
    }

    // for cheating...
    void Die::setValue( int amount )
    {
        mValue = amount;
    }

}
