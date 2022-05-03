

#include <iostream>
using namespace std;
#include <string>
#include <cassert>
#include <cmath>
#include <cctype>

//DECLARING FUNCTIONS
bool isValidCDPlayerString(string cdstring);
bool isOpen(string cdstring);
bool isOpenMine(string cdstring, size_t i);
bool isPlayingMine(string cdstring, size_t i);
bool hasCDMine(string cdstring, size_t i);
bool isEmptyMine(string cdstring, size_t i);
bool inAscendingMine(string cdstring, size_t i);
bool hasCD(string cdstring);
int totalTracksPlayed(string cdstring);
int currentTrack(string cdstring);

int main() {
    
    string cdstring = "";
    getline(cin, cdstring);
    cout<<isValidCDPlayerString(cdstring);
    
    assert( isOpen("OCOCOCO") == true);
    assert( isOpen("OICP123SO") == true);
    assert( isOpen("OICP123SOO") == false);
    assert( isOpen("OICP123SO") == true);
    assert( hasCD("OICP123S") == true);
    assert( hasCD("OICP123SOR") == false);
    assert( hasCD("OICOP123SOR") == false);
    assert( totalTracksPlayed("OICP123ORICP1234S") == 7);
    assert( totalTracksPlayed("OIRCPS") == -1);
    assert( totalTracksPlayed("OICPS") == 0);
    assert( currentTrack("OIC") == 1);
    assert( currentTrack("OICP123S") == 4);
    assert( currentTrack("OICP123SOR") == -1);
    assert( isValidCDPlayerString("OICPS") == true);
    assert( isValidCDPlayerString("OICP123OS") == true);
    assert( isValidCDPlayerString("OICP123ORCS") == true);
    assert( isValidCDPlayerString("OICP123ORICSPSP1") == true);
    assert( isValidCDPlayerString("OICP123PPPPPPPS") == true);
    assert( isValidCDPlayerString("OICP123OC456") == false);
    assert( isValidCDPlayerString("OICP1P2P3P4S") == true);
    
}

bool isValidCDPlayerString(string cdstring)
{
    //if string is empty
    if (cdstring.size() == 0) {
        return false;
    }
    //if string not empty
    bool result = true;
    for (size_t i = 0; i < cdstring.size() ; i++ )
    {
        //Check if string starts with 'O'
        if (cdstring[i] == 'O' && i == 0) {
            result=result;
        }
        
        
        //'I' found
        else if (cdstring[i] == 'I') {
            
            //Check if player open
            isOpenMine(cdstring, i);
            if (isOpenMine(cdstring, i) == true) {
                result = result;
            }
            else {
                return false;
            }
            
            //Check if player empty
            isEmptyMine(cdstring, i);
            if (isEmptyMine(cdstring, i) == true) {
                result = result;
            }
            else {
                return false;
            }
        }
        
        
        // 'R' found
        else if (cdstring[i] == 'R') {
            
            //Check if CD inside
            hasCDMine(cdstring, i);
            if (hasCDMine(cdstring, i) == true) {
                result = result;
            }
            else {
                return false;
            }
            
            //Check if player open
            isOpenMine(cdstring, i);
            if (isOpenMine(cdstring, i) == true) {
                result = result;
            }
            else {
                return false;
            }
            
        }
        
        //'C' found
        else if (cdstring[i] == 'C') {
            
            //Check if player open
            isOpenMine(cdstring, i);
            if (isOpenMine(cdstring, i) == true) {
                result = result;
            }
            else {
                return false;
            }
        }
        
        //'O' found
        else if (cdstring[i] == 'O') {
            
            //Check if player closed
            isOpenMine(cdstring, i);
            if (isOpenMine(cdstring, i) == false) {
                result = result;
            }
            else {
                return false;
            }
        }
        
        //'P' found
        else if (cdstring[i] == 'P') {
            
            //Check if player closed
            isOpenMine(cdstring, i);
            if (isOpenMine(cdstring, i) == false) {
                result = result;
            }
            else {
                return false;
            }
            
            //Check if CD inside
            hasCDMine(cdstring, i);
            if (hasCDMine(cdstring, i) == true) {
                result = result;
            }
            else {
                return false;
            }
        }
        
        
        //'S' found
        else if (cdstring[i] == 'S') {
            
            //Check if cd is playing
            isPlayingMine(cdstring, i);
            if (isPlayingMine(cdstring, i) == true) {
                result = result;
            }
            else {
                return false;
            }
        }
        
        
        //Numbers found
        else if (cdstring[i] >= 49 && cdstring[i] <= 57) {
            
            //Check if numbers in ascending order
            inAscendingMine(cdstring, i);
            if (inAscendingMine(cdstring, i) == true) {
                result = result;
            }
            else {
                return false;
            }
            
            //Check if before this number, there is a P
            if (cdstring[i-1] == 'P') {
                result = result;
            }
            
            //Check if before this number, there is another number that is one less
            else if (cdstring[i-1] == cdstring[i] - 1) {
                result = result;
            }
            else {
                return false;
            }
            
            
        }
        
        
        //Empty string or spacing returns false
        else if (cdstring[i] == ' ') {
            return false;
        }
        
        else {
            return false;
        }
    }
    
    return result;
}

//WRITING OF FUNCTIONS

//Own function to check for P or S
bool isPlayingMine(string cdstring, size_t i) {
    bool isPlaying = false;
    for (size_t j = 0; j < i; j++) {
        if (cdstring[j] == 'P') {
            isPlaying = true;
        }
        else if (cdstring[j] == 'S') {
            isPlaying = false;
        }
    }
    return isPlaying;
}
    
//Own function to check for I and R
bool hasCDMine(string cdstring, size_t i) {
    bool hasCD = false;
    for (size_t j = 0; j < i ; j++) {
        if (cdstring[j] == 'I') {
            hasCD = true;
        }
        else if (cdstring[j] == 'R') {
            hasCD = false;
        }
    }
    return hasCD;
}

//Own function to check for R and I
bool isEmptyMine(string cdstring, size_t i) {
    bool isEmpty = true;
    for (size_t j = 0; j < i ; j++) {
        if (cdstring[j] == 'R') {
            isEmpty = true;
        }
        else if (cdstring[j] == 'I') {
            isEmpty = false;
        }
    }
    return isEmpty;
}

//Own function to check if numbers are in ascending order
bool inAscendingMine(string cdstring, size_t i) {
    bool inOrder = true;
    size_t startingNo1 = 49;
    for (size_t j = 0; j < i ; j++) {
        if (cdstring[j] >= 49 && cdstring[j] <= 57) {
            if (cdstring[j] == startingNo1) {
                startingNo1++;
                inOrder = true;
            }
            else if (cdstring[j] == 'P') {
                inOrder = inOrder;
            }
            
            else {
                return false;
            }
        }
        
        else if (cdstring[j] == 'R'){
            startingNo1 = 49;
        }
    }
    return inOrder;
}

//Own function to check for O and C
bool isOpenMine(string cdstring, size_t i) {
    bool isOpen = true;
    for (size_t j = 0; j < i ; j++) {
        if (cdstring[j] == 'O') {
            isOpen = true;
        }
        else if (cdstring[j] == 'C') {
            isOpen = false;
        }
    }
    return isOpen;
}

//Check that player is Open or Closed at the end
bool isOpen(string cdstring) {
    bool isOpeney = true;
    if (isValidCDPlayerString(cdstring)) {
        
        for (size_t i = 0; i < cdstring.size() ; i++) {
            if (cdstring[i] == 'O') {
                isOpeney = true;
            }
            else if (cdstring[i] == 'C') {
                isOpeney = false;
            }
        }
    }
    else {
        return false;
    }
    return isOpeney;
    
}

//Check that player has CD or not at the end
bool hasCD(string cdstring) {
    bool CDInside = false;
    if (isValidCDPlayerString(cdstring)) {
        for (size_t i = 0 ; i <cdstring.size() ; i++) {
            if (cdstring[i] == 'I') {
                CDInside = true;
            }
            else if (cdstring[i] == 'R') {
                CDInside = false;
            }
        }
    }
    
    else {
        return false;
    }
    return CDInside;
}

//Counts the total number of tracks
int totalTracksPlayed(string cdstring) {
    int tracksPlayed = 0;
    if (isValidCDPlayerString(cdstring)) {
        for (size_t i = 0 ; i <cdstring.size() ; i++) {
            if (cdstring[i] >=49 && cdstring[i] <= 57) {
                tracksPlayed++;
            }
        }
    }
    else {
        return -1;
    }
    return tracksPlayed;
}

//Returns the current track
int currentTrack(string cdstring) {
    int nextTrack = -1;
    if (isValidCDPlayerString(cdstring)) {
        for (size_t i = 0 ; i < cdstring.size() ; i++) {
            if (cdstring[i] == 'I') {
                nextTrack = 1;
            }
            else if (cdstring[i] == 'R') {
                nextTrack = -1;
            }
            else if (cdstring[i] >= 49 && cdstring[i] <= 57) {
                nextTrack = cdstring[i] - 47;
            }
        }
    }
    else {
        return -1;
    }
    return nextTrack;
}




































