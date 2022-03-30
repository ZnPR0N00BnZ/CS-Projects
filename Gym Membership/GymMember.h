#include <iostream>
#include "Kind.h"

#ifndef GymMember_h
#define GymMember_h


class GymMember {
private:
    std::string mName;
    std::string mAccountNumber;
    kind mKind;
    int mWorkOutCount;
    
public:
    GymMember(std::string name,std::string accountnumber, kind Kind);
    
    int workoutsThisMonth();
    
    void startNewMonth();
    
    void newWorkout();
    
    kind getKind();
    
    std::string getKindAsString();
    
    std::string getName();
    
    std::string getAccountNumber();
};

#endif /* GymMember_h */

