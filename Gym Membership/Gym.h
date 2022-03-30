#include <iostream>
#include "Kind.h"
#include "GymMember.h"

#ifndef Gym_h
#define Gym_h

class Gym {
private:
    std::string mName;
    std::string mLocation;
    kind mKind;
    bool hasCardio = false;
    bool hasWeights = false;
    bool hasPool = false;
    bool hasTrack = false;
    
public:
    Gym(std::string name, std::string location, kind Kind);
    
    void setFeatures(bool cardio, bool weights, bool pool, bool track);
    
    bool canWorkoutHere(GymMember person);
    
    bool checkin (GymMember & person, bool wantsCardio, bool wantsWeights, bool wantsPool, bool wantsTrack);
    
    //4 features
    bool hasCardioFeatures();
    
    bool hasWeightsFeatures();
    
    bool hasPoolFeatures();
    
    bool hasTrackFeatures();
    
    //Getters
    kind getKind();
    
    std::string getKindAsString();
    
    std::string getLocation();
    
    std::string getName();
};

#endif /* Gym_h */
