
#include "GymMember.h"
#include "Gym.h"
#include <iostream>
#include <cassert>
using namespace std;



void testone(int n)
{
   Gym g_executive( "SportsClubLA", "West Los Angeles", EXECUTIVE );
   Gym g_premier("24 Hour Fitness", "Santa Monica", PREMIER );
   Gym g_regular("Joe's Gym", "Sherman Oaks", REGULAR );

   GymMember m_executive( "Howard", "66666", EXECUTIVE );
   GymMember m_premier( "Bill", "54321", PREMIER );
   GymMember m_regular( "Sam", "12345", REGULAR );
   
   switch (n)
   {
        case  1:
                assert( m_regular.getKind() == REGULAR );
                assert( m_regular.getKindAsString() == "Regular" || m_regular.getKindAsString() == "REGULAR" );
                assert( m_regular.getName() == "Sam" );
                assert( m_regular.getAccountNumber() == "12345" );
                assert( m_regular.workoutsThisMonth() == 0 );
                assert( m_premier.getKindAsString() == "Premier" || m_premier.getKindAsString() == "PREMIER" );
                assert( m_premier.getKind() == PREMIER );
                assert( m_executive.getKindAsString() == "Executive" || m_executive.getKindAsString() == "EXECUTIVE" );
                assert( m_executive.getKind() == EXECUTIVE );
                break;
        case  2:
                m_regular.startNewMonth();
                assert( m_regular.workoutsThisMonth() == 0 );
                break;
        case  3:
                m_regular.startNewMonth();
                m_regular.newWorkout();
                m_regular.newWorkout();
                assert( m_regular.workoutsThisMonth() == 2 );
                
                m_regular.startNewMonth();
                m_regular.newWorkout();
                assert( m_regular.workoutsThisMonth() == 1 );
                break;
        case  4:
                assert( g_regular.getKind() == REGULAR );
                assert( g_regular.getKindAsString() == "Regular" || g_regular.getKindAsString() == "REGULAR" );
                assert( g_regular.getName() == "Joe's Gym" );
                assert( g_regular.getLocation() == "Sherman Oaks" );
                assert( g_premier.getKindAsString() == "Premier" || g_premier.getKindAsString() == "PREMIER" );
                assert( g_premier.getKind() == PREMIER );
                assert( g_executive.getKindAsString() == "Executive" || g_executive.getKindAsString() == "EXECUTIVE" );
                assert( g_executive.getKind() == EXECUTIVE );
                break;
        case  5:
                assert( g_regular.hasCardioFeatures() == false );
                assert( g_regular.hasWeightsFeatures() == false );
                assert( g_regular.hasPoolFeatures() == false );
                assert( g_regular.hasTrackFeatures() == false );
                break;
        case  6:
                g_regular.setFeatures( true, false, false, false );
                assert( g_regular.hasCardioFeatures() == true );
                assert( g_regular.hasWeightsFeatures() == false );
                assert( g_regular.hasPoolFeatures() == false );
                assert( g_regular.hasTrackFeatures() == false );
                break;
        case  7:
                g_regular.setFeatures( false, true, false, false );
                assert( g_regular.hasCardioFeatures() == false );
                assert( g_regular.hasWeightsFeatures() == true );
                assert( g_regular.hasPoolFeatures() == false );
                assert( g_regular.hasTrackFeatures() == false );
                break;
        case  8:
                g_regular.setFeatures( false, false, true, false );
                assert( g_regular.hasCardioFeatures() == false );
                assert( g_regular.hasWeightsFeatures() == false );
                assert( g_regular.hasPoolFeatures() == true );
                assert( g_regular.hasTrackFeatures() == false );
                break;
        case  9:
                g_regular.setFeatures( false, false, false, true );
                assert( g_regular.hasCardioFeatures() == false );
                assert( g_regular.hasWeightsFeatures() == false );
                assert( g_regular.hasPoolFeatures() == false );
                assert( g_regular.hasTrackFeatures() == true );
                break;
        case 10:
                m_regular.startNewMonth();
                assert( m_regular.workoutsThisMonth() == 0 );
                assert( g_regular.canWorkoutHere( m_regular ) == true );
                g_regular.checkin( m_regular, false, false, false, false );
                assert( m_regular.workoutsThisMonth() == 1 );
                g_regular.checkin( m_regular, true, false, false, false );
                assert( m_regular.workoutsThisMonth() == 1 );
                g_regular.checkin( m_regular, false, true, false, false );
                assert( m_regular.workoutsThisMonth() == 1 );
                g_regular.checkin( m_regular, false, false, true, false );
                assert( m_regular.workoutsThisMonth() == 1 );
                g_regular.checkin( m_regular, false, false, false, true );
                assert( m_regular.workoutsThisMonth() == 1 );
                break;
        case 11:
                m_regular.startNewMonth();
                assert( m_regular.workoutsThisMonth() == 0 );
                assert( g_premier.canWorkoutHere( m_regular ) == false );
                g_premier.checkin( m_regular, false, false, false, false );
                assert( m_regular.workoutsThisMonth() == 0 );
                g_premier.checkin( m_regular, true, false, false, false );
                assert( m_regular.workoutsThisMonth() == 0 );
                g_premier.checkin( m_regular, false, true, false, false );
                assert( m_regular.workoutsThisMonth() == 0 );
                g_premier.checkin( m_regular, false, false, true, false );
                assert( m_regular.workoutsThisMonth() == 0 );
                g_premier.checkin( m_regular, false, false, false, true );
                assert( m_regular.workoutsThisMonth() == 0 );
                break;
        case 12:
                m_regular.startNewMonth();
                assert( m_regular.workoutsThisMonth() == 0 );
                assert( g_executive.canWorkoutHere( m_regular ) == false );
                g_executive.checkin( m_regular, false, false, false, false );
                assert( m_regular.workoutsThisMonth() == 0 );
                g_executive.checkin( m_regular, true, false, false, false );
                assert( m_regular.workoutsThisMonth() == 0 );
                g_executive.checkin( m_regular, false, true, false, false );
                assert( m_regular.workoutsThisMonth() == 0 );
                g_executive.checkin( m_regular, false, false, true, false );
                assert( m_regular.workoutsThisMonth() == 0 );
                g_executive.checkin( m_regular, false, false, false, true );
                assert( m_regular.workoutsThisMonth() == 0 );
                break;
        case 13:
                m_premier.startNewMonth();
                assert( m_premier.workoutsThisMonth() == 0 );
                assert( g_executive.canWorkoutHere( m_premier ) == false );
                g_executive.checkin( m_premier, false, false, false, false );
                assert( m_premier.workoutsThisMonth() == 0 );
                g_executive.checkin( m_premier, true, false, false, false );
                assert( m_premier.workoutsThisMonth() == 0 );
                g_executive.checkin( m_premier, false, true, false, false );
                assert( m_premier.workoutsThisMonth() == 0 );
                g_executive.checkin( m_premier, false, false, true, false );
                assert( m_premier.workoutsThisMonth() == 0 );
                g_executive.checkin( m_premier, false, false, false, true );
                assert( m_premier.workoutsThisMonth() == 0 );
                break;
        case 14:
                m_premier.startNewMonth();
                assert( m_premier.workoutsThisMonth() == 0 );
                assert( g_regular.canWorkoutHere( m_premier ) == true );
                g_regular.checkin( m_premier, false, false, false, false );
                assert( m_premier.workoutsThisMonth() == 1 );
                g_regular.checkin( m_premier, true, false, false, false );
                assert( m_premier.workoutsThisMonth() == 1 );
                g_regular.checkin( m_premier, false, true, false, false );
                assert( m_premier.workoutsThisMonth() == 1 );
                g_regular.checkin( m_premier, false, false, true, false );
                assert( m_premier.workoutsThisMonth() == 1 );
                g_regular.checkin( m_premier, false, false, false, true );
                assert( m_premier.workoutsThisMonth() == 1 );
                break;
        case 15:
                m_premier.startNewMonth();
                assert( m_premier.workoutsThisMonth() == 0 );
                assert( g_premier.canWorkoutHere( m_premier ) == true );
                g_premier.checkin( m_premier, false, false, false, false );
                assert( m_premier.workoutsThisMonth() == 1 );
                g_premier.checkin( m_premier, true, false, false, false );
                assert( m_premier.workoutsThisMonth() == 1 );
                g_premier.checkin( m_premier, false, true, false, false );
                assert( m_premier.workoutsThisMonth() == 1 );
                g_premier.checkin( m_premier, false, false, true, false );
                assert( m_premier.workoutsThisMonth() == 1 );
                g_premier.checkin( m_premier, false, false, false, true );
                assert( m_premier.workoutsThisMonth() == 1 );
                break;
        case 16:
                m_executive.startNewMonth();
                assert( m_executive.workoutsThisMonth() == 0 );
                assert( g_executive.canWorkoutHere( m_executive ) == true );
                g_executive.checkin( m_executive, false, false, false, false );
                assert( m_executive.workoutsThisMonth() == 1 );
                g_executive.checkin( m_executive, true, false, false, false );
                assert( m_executive.workoutsThisMonth() == 1 );
                g_executive.checkin( m_executive, false, true, false, false );
                assert( m_executive.workoutsThisMonth() == 1 );
                g_executive.checkin( m_executive, false, false, true, false );
                assert( m_executive.workoutsThisMonth() == 1 );
                g_executive.checkin( m_executive, false, false, false, true );
                assert( m_executive.workoutsThisMonth() == 1 );
                break;
        case 17:
                m_executive.startNewMonth();
                assert( m_executive.workoutsThisMonth() == 0 );
                assert( g_regular.canWorkoutHere( m_executive ) == true );
                g_regular.checkin( m_executive, false, false, false, false );
                assert( m_executive.workoutsThisMonth() == 1 );
                g_regular.checkin( m_executive, true, false, false, false );
                assert( m_executive.workoutsThisMonth() == 1 );
                g_regular.checkin( m_executive, false, true, false, false );
                assert( m_executive.workoutsThisMonth() == 1 );
                g_regular.checkin( m_executive, false, false, true, false );
                assert( m_executive.workoutsThisMonth() == 1 );
                g_regular.checkin( m_executive, false, false, false, true );
                assert( m_executive.workoutsThisMonth() == 1 );
                break;
        case 18:
                m_executive.startNewMonth();
                assert( m_executive.workoutsThisMonth() == 0 );
                assert( g_premier.canWorkoutHere( m_executive ) == true );
                g_premier.checkin( m_executive, false, false, false, false );
                assert( m_executive.workoutsThisMonth() == 1 );
                g_premier.checkin( m_executive, true, false, false, false );
                assert( m_executive.workoutsThisMonth() == 1 );
                g_premier.checkin( m_executive, false, true, false, false );
                assert( m_executive.workoutsThisMonth() == 1 );
                g_premier.checkin( m_executive, false, false, true, false );
                assert( m_executive.workoutsThisMonth() == 1 );
                g_premier.checkin( m_executive, false, false, false, true );
                assert( m_executive.workoutsThisMonth() == 1 );
                break;
        case 19:
                g_regular.setFeatures( false, false, true, true );
                m_regular.startNewMonth();
                assert( m_regular.workoutsThisMonth() == 0 );
                assert( g_regular.canWorkoutHere( m_regular ) == true );
                g_regular.checkin( m_regular, false, false, false, false );
                assert( m_regular.workoutsThisMonth() == 1 );
                g_regular.checkin( m_regular, true, false, false, false );
                assert( m_regular.workoutsThisMonth() == 1 );
                g_regular.checkin( m_regular, false, true, false, false );
                assert( m_regular.workoutsThisMonth() == 1 );
                g_regular.checkin( m_regular, false, false, true, false );
                assert( m_regular.workoutsThisMonth() == 2 );
                g_regular.checkin( m_regular, false, false, false, true );
                assert( m_regular.workoutsThisMonth() == 3 );
                break;
        case 20:
                g_premier.setFeatures( false, true, false, true );
                m_premier.startNewMonth();
                assert( m_premier.workoutsThisMonth() == 0 );
                assert( g_premier.canWorkoutHere( m_premier ) == true );
                g_premier.checkin( m_premier, false, false, false, false );
                assert( m_premier.workoutsThisMonth() == 1 );
                g_premier.checkin( m_premier, true, false, false, false );
                assert( m_premier.workoutsThisMonth() == 1 );
                g_premier.checkin( m_premier, false, true, false, false );
                assert( m_premier.workoutsThisMonth() == 2 );
                g_premier.checkin( m_premier, false, false, true, false );
                assert( m_premier.workoutsThisMonth() == 2 );
                g_premier.checkin( m_premier, false, false, false, true );
                assert( m_premier.workoutsThisMonth() == 3 );
                break;
        case 21:
                g_executive.setFeatures( true, true, false, false );
                m_executive.startNewMonth();
                assert( m_executive.workoutsThisMonth() == 0 );
                assert( g_executive.canWorkoutHere( m_executive ) == true );
                g_executive.checkin( m_executive, false, false, false, false );
                assert( m_executive.workoutsThisMonth() == 1 );
                g_executive.checkin( m_executive, true, false, false, false );
                assert( m_executive.workoutsThisMonth() == 2 );
                g_executive.checkin( m_executive, false, true, false, false );
                assert( m_executive.workoutsThisMonth() == 3 );
                g_executive.checkin( m_executive, false, false, true, false );
                assert( m_executive.workoutsThisMonth() == 3 );
                g_executive.checkin( m_executive, false, false, false, true );
                assert( m_executive.workoutsThisMonth() == 3 );
                break;

         default:
                cout << "Bad argument" ;
                break;
    }
}

int main()
{
    cout << "Enter test number: ";
    int n;
    cin >> n;
    testone(n);
    cout << "It works!" << endl;
    return( 0 );
}
