
// Towers of Hanoi with state saving in stacks

#include <iostream>
#include "arrayStack.h"

using namespace std;

// global variable, tower[1:3] are the three towers
arrayStack<int> tower[4];

void moveAndShow(int, int, int, int);

void showState()
{
    for (int i = 1; i <= 3; i++)
    {
        std::cout << "tower " << i << ": ";
        tower[i].output(std::cout);
        std::cout << endl;
    }
}

void towersOfHanoi(int n)
{// Preprocessor for moveAndShow.
    for (int d = n; d > 0; d--) // initialize
        tower[1].push(d); // add disk d to tower 1

     // move n disks from tower 1 to 3 using 2 as
     // intermediate tower
    showState();
    moveAndShow(n, 1, 2, 3);
}

void moveAndShow(int n, int x, int y, int z)
{// Move the top n disks from tower x to tower y showing states.
 // Use tower z for intermediate storage.
    if (n > 0)
    {
        moveAndShow(n - 1, x, z, y);
        int d = tower[x].top();   // move a disk from top of
        tower[x].pop();           // tower x to top of
        tower[y].push(d);         // tower y
        cout << "Move disk " << d << " from tower "
            << x << " to top of tower " << y << endl;
        showState();              // show state of 3 towers
     // substitute showState code for test run
        moveAndShow(n - 1, z, y, x);
    }
}

void testHanioUsingStackS()
{
    cout << "Moves for a three disk problem are" << endl;
    towersOfHanoi(5);
}
