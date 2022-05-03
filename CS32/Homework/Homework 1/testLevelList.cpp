

#include "LevelList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
    LevelList list;
    assert( list.size() == 0);
    list.add(20);
    list.add(30);
    assert( list.size() == 1);
    list.add(40);
    list.add(401);
    list.add(50);
    assert( list.size() == 3);
    assert( list.minimum() == 30);
    list.remove(30);
    assert( list.minimum() == 40);
    assert( list.size() == 2);
    assert( list.maximum() == 50);
    cout << "Passed!";
}



