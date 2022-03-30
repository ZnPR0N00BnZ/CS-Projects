
#include <iostream>
#include "Kind.h"
#include "GymMember.h"

//initialising constructor
GymMember::GymMember(std::string name,std::string accountnumber, kind Kind) {
    mName = name;
    mAccountNumber = accountnumber;
    mKind = Kind;
    mWorkOutCount = 0;
}


int GymMember::workoutsThisMonth(){
    return mWorkOutCount;
}


void GymMember::startNewMonth() {
    mWorkOutCount = 0;
}


void GymMember::newWorkout() {
    mWorkOutCount++;
}


kind GymMember::getKind() {
    return mKind;
}


std::string GymMember::getKindAsString()
{
    std::string result = "";
    switch( mKind )
    {
        case OTHER:
            result = "Other";
            break;

        case REGULAR:
            result = "Regular";
            break;

        case PREMIER:
            result = "Premier";
            break;

        case EXECUTIVE:
            result = "Executive";
            break;
    }
    return( result );
}


std::string GymMember::getName() {
    return mName;
}


std::string GymMember::getAccountNumber() {
    return mAccountNumber;
}
