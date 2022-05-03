//
//  main.cpp
//  Bunco
//
//  Created by Howard Stahl on 1/27/17.
//  Copyright © 2017 Howard Stahl. All rights reserved.
//

#include <iostream>
#include "Die.h"
#include "Player.h"
#include "Bunco.h"


void clearScreen( );



int main()
{
    using namespace std;
    using namespace cs31;

    // Die class
    // Test randomness is between 1 and 6, inclusive
    Die d;
    for (int i = 1; i <= 100; i++) {
        d.roll();
        int value = d.getValue();
        assert(value >= 1 && value <= 6);
    }

    // Player class
    // Tests dice rolling and score
    Player p;
    for (int i = 1; i <= 6; i++) {
        p.setRound(i);
        assert(p.getScore() == 0);
        assert(p.roll(i) == i);
        assert(p.getScore() == 1);
    }

    Die d1;
    d1.setValue(1);
    Die d2;
    d2.setValue(2);
    Die d3;
    d3.setValue(3);
    Die d4;
    d4.setValue(4);
    Die d5;
    d5.setValue(5);
    Die d6;
    d6.setValue(6);

    Die dies[] = {d1, d2, d3, d4, d5, d6};

    // Bunco class
    // Human wins every round, wins game
    Bunco b_h;
    for (int i = 0; i < 6; i++) {
        b_h.humanPlay(dies[i]);
        b_h.computerPlay(dies[i]);
        b_h.endTurn();
        assert(b_h.determineRoundOutcome() == Bunco::NOTDECIDED);

        b_h.humanPlay(dies[i]);
        b_h.computerPlay(
            dies[(i + 1) % 6]);  // When i + 1 is greater than 5, wraps to 1
        b_h.endTurn();
        assert(b_h.determineRoundOutcome() == Bunco::HUMANWON);

        // Check if game is over before last round is played
        if (i < 5) {
            assert(b_h.determineGameOutcome() == Bunco::GAMENOTOVER);
        }

        b_h.nextRound();
    }
    assert(b_h.determineGameOutcome() == Bunco::HUMANWONGAME);

    // Computer wins every round, wins game
    Bunco b_c;
    for (int j = 0; j < 6; j++) {
        b_c.humanPlay(dies[j]);
        b_c.computerPlay(dies[j]);
        b_c.endTurn();
        assert(b_c.determineRoundOutcome() == Bunco::NOTDECIDED);

        b_c.humanPlay(
            dies[(j + 1) % 6]);  // When i + 1 is greater than 5, wraps to 1
        b_c.computerPlay(dies[j]);
        b_c.endTurn();
        assert(b_c.determineRoundOutcome() == Bunco::COMPUTERWON);

        // Check if game is over before last round is played
        if (j < 5) {
            assert(b_c.determineGameOutcome() == Bunco::GAMENOTOVER);
        }

        b_c.nextRound();
    }
    assert(b_c.determineGameOutcome() == Bunco::COMPUTERWONGAME);

    // Player wins odd rounds, computer wins even rounds, game is tied
    Bunco b_t;
    for (int k = 0; k < 6; k++) {
        b_t.humanPlay(dies[k]);
        b_t.computerPlay(dies[k]);
        b_t.endTurn();
        assert(b_t.determineRoundOutcome() == Bunco::NOTDECIDED);

        if (k % 2 == 1) {
            b_t.humanPlay(dies[k]);
            b_t.computerPlay(
                dies[(k + 1) % 6]);  // When i + 1 is greater than 5, wraps to 1
            b_t.endTurn();
            assert(b_t.determineRoundOutcome() == Bunco::HUMANWON);
        } else {
            b_t.humanPlay(
                dies[(k + 1) % 6]);  // When i + 1 is greater than 5, wraps to 1
            b_t.computerPlay(dies[k]);
            b_t.endTurn();
            assert(b_t.determineRoundOutcome() == Bunco::COMPUTERWON);
        }

        // Check if game is over before last round is played
        if (k < 5) {
            assert(b_t.determineGameOutcome() == Bunco::GAMENOTOVER);
        }

        b_t.nextRound();
    }
    assert(b_t.determineGameOutcome() == Bunco::TIEDGAME);

    cerr << "All tests passed! (ﾉ◕ヮ◕)ﾉ*:･ﾟ✧" << endl;
    return 0;
}


void clearScreen();



///////////////////////////////////////////////////////////////////////////
//  clearScreen implementations
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++ UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <cstring>

void clearScreen()  // will just write a newline in an Xcode output window
{
    using namespace std;
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
    {
        cout << endl << endl << endl << endl << endl << endl << endl << endl;;
    }
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif

