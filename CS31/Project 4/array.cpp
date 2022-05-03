
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

//Declare Functions
int locateMinimum( const  string  array[ ],  int  n );
int countCommonElements( const string array1[ ], int  n1, const string array2[ ], int n2 );
int countVowels( const string array[ ], int n );
bool hasThreeOfX( const string array[ ], int n, string x );
string majorityElement( const string array[ ], int  n );
bool shiftRight( string array[ ], int n, int amount, string placeholder );
bool rotateLeft( string array[ ], int n, int amount );
int replaceAll( string array[ ], int n, char letterToReplace, char letterToFill );


int main() {

}

//Defining Functions
//First
int locateMinimum( const  string  array[ ],  int  n ) {
    if (n <= 0) {
        return -1;
    }
    else {
        string currentMin = array[0];
        int currentMinIndex = 0;
        for (int pos = 0 ; pos < n ; pos++) {
            if (array[pos] < currentMin) {
                currentMin = array[pos];
                currentMinIndex = pos;
            }
        }
        return currentMinIndex;
    }
}

//Second
int countCommonElements( const string array1[ ], int  n1, const string array2[ ], int n2 ) {
    if (n1 <=0 || n2 <= 0) {
        return -1;
    }
    else{
        int noOfCommonElems = 0;
        for (size_t pos1 = 0 ; pos1 < n1; pos1++) {
            for (size_t pos2 = 0; pos2 < n2; pos2++) {
                if (array1[pos1] == array2[pos2]) {
                    noOfCommonElems++;
                }
            }
        }
        return noOfCommonElems;
    }
}

//Third
int countVowels( const string array[ ], int n ) {
    if (n <= 0) {
        return -1;
    }
    else {
        int noOfVowels = 0;
        for (size_t pos = 0 ; pos < n ; pos++) {
            for (size_t letter = 0 ; letter < array[pos].size() ; letter++) {
                switch (array[pos][letter]) {
                    case 'a':
                    case 'e':
                    case 'i':
                    case 'o':
                    case 'u':
                    case 'y':
                    case 'A':
                    case 'E':
                    case 'I':
                    case 'O':
                    case 'U':
                    case 'Y':
                        noOfVowels++;
                    default:
                    {}
                }
            }
        } return noOfVowels;
        
    }
}

//Fourth
bool hasThreeOfX( const string array[ ], int n, string x ) {
    if (n <= 0) {
        return false;
    }
    else {
    int noOfX = 0;
    for (size_t pos = 0 ; pos < n ; pos++) {
        if (array[pos] == x) {
            noOfX++;
        }
    }
    return noOfX == 3;
    }
}

//Fifth
string majorityElement( const string array[ ], int  n ) {
    //1st Loop
    if (n <= 0) {
        return "";
    }
    for (size_t pos1 = 0 ; pos1 < n ; pos1++) {
        int noOfDuplicates = 0;
        string toBeTested = array[pos1];
        
        //2nd Loop to test all characters against current one
        for (size_t pos2 = pos1; pos2 < n; pos2++) {
            if (array[pos2] == toBeTested) {
                noOfDuplicates++;
            }
        }
        if (noOfDuplicates > n/2) {
            return toBeTested;
        }
    }
    return "";
}

//Sixth
bool shiftRight( string array[ ], int n, int amount, string placeholder ) {
    if (amount <= 0 || n <= 0) {
        return false;
    }
    else {
        for (size_t loop = 0 ; loop < amount; loop++) {
            for (size_t pos = n-1; pos != 0; pos--) {
                array[pos] = array[pos-1];
            }
            array[0] = placeholder;
        }
        return true;
    }
}

//Seventh
bool rotateLeft( string array[ ], int n, int amount ) {
    if (n <= 0 || amount % n == 0) {
        return false;
    }
    else {
        for (size_t loopNum = 0 ; loopNum < amount; loopNum++) {
            //variable temp = first element
            string temp = array[0];
            for (size_t pos = 0 ; pos < n-1; pos++) {
                array[pos] = array[pos+1];
            }
            //replaces last element with first element using temp
            array[n-1] = temp;
        }
    }
    return true;
}

//Eighth
int replaceAll( string array[ ], int n, char letterToReplace, char letterToFill ) {
    int noOfSwaps = 0;
    if (n <= 0) {
        return -1;
    }
    else {
        for (size_t pos = 0 ; pos < n ; pos++) {
            //iterating across the strings
            for (size_t letter = 0 ; letter < array[pos].size() ; letter++) {
                if (array[pos][letter] == letterToReplace) {
                    array[pos][letter] = letterToFill;
                    noOfSwaps++;
                }
            }
        }
    }
    return noOfSwaps;
}
