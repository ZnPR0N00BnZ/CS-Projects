
#include <iostream>
#include "Gym.h"
#include "Kind.h"
#include "GymMember.h"

//initialising constructor
Gym:: Gym(std::string name, std::string location, kind Kind) {
    mName = name;
    mLocation = location;
    mKind = Kind;
}

void Gym::setFeatures(bool cardio, bool weights, bool pool, bool track) {
    hasCardio = cardio;
    hasWeights = weights;
    hasPool = pool;
    hasTrack = track;
}

//comparing memberType and gymType to determine if they can workout here
bool Gym::canWorkoutHere( GymMember m )
{
    bool result = false;
    
    if (m.getKind() == getKind())
    {
        result = true;
    }
    // premier get into regular gyms
    else if (m.getKind() == PREMIER && getKind() == REGULAR )
    {
        result = true;
    }
    // executive get into regular and premier gyms
    else if (m.getKind() == EXECUTIVE && (getKind() == REGULAR || getKind() == PREMIER ))
    {
        result = true;
    }
    
    return( result );
}


//if their wants are false, nothing happens. Otherwise ensure that gym has specific feature that member wants
bool Gym::checkin (GymMember & person, bool wantsCardio, bool wantsWeights, bool wantsPool, bool wantsTrack){
    if (canWorkoutHere(person) == false) {
        return false;
    }
    
    if (wantsCardio == false) {}
    else if (wantsCardio == true && hasCardioFeatures() == false) {
        return false;
    }
    if (wantsWeights == false) {}
    else if (wantsWeights == true && hasWeightsFeatures() == false) {
        return false;
    }
    if (wantsPool == false) {}
    else if (wantsPool == true && hasPoolFeatures() == false) {
        return false;
    }
    if (wantsTrack == false) {}
    else if (wantsTrack == true && hasTrackFeatures() == false) {
        return false;
    }
    person.newWorkout();
    return true;
}

bool Gym::hasCardioFeatures() {
    return hasCardio;
}
bool Gym::hasWeightsFeatures() {
    return hasWeights;
}
bool Gym::hasPoolFeatures() {
    return hasPool;
}
bool Gym::hasTrackFeatures(){
    return hasTrack;
}

//Getters
kind Gym::getKind() {
    return mKind;
}

std::string Gym::getKindAsString() {
    
    std::string mKindString = std::to_string(mKind);
    if (mKindString == "1") {
        return "REGULAR";
    }
    else if (mKindString == "2") {
        return "PREMIER";
    }
    else if (mKindString == "3") {
        return "EXECUTIVE";
    }
    else {
        return "OTHER";
    }
}

std::string Gym:: getLocation() {
    return mLocation;
}
std::string Gym::getName(){
    return mName;
}
