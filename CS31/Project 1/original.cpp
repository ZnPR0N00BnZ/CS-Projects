//
//  Code for Project 1
//  UCLA Classes

#include <iostream>
#include <string>
using namespace std;

int main()
{
    string department;        // the department being analyzed
    int onground, online, total;   // course sections offered
    
    cout << "What academic department are we reviewing? ";
    getline( cin, department );
    cout << "How many sections are being offered? ";
    cin >> total;
    cout << "How many of these sections are happening on-ground? ";
    cin >> onground;
    cout << "How many of these sections are happening on-line? ";
    cin >> online;
    
    double percentage = 100.0 * onground / (onground + online);
    
    cout.setf(ios::fixed);  // see pp. 30-31 in Savitch book
    cout.precision(1);
    
    cout << endl;
    cout << percentage << "% of the " << department << " sections occurred on-ground." << endl;
 
    if (onground < 0 || online < 0 || total != onground + online)
    {
        cout << "Looks like some of these values don't make sense." << endl;
    }

    return(0);
}
