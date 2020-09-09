#include "src/NBGame.h"
#include<cstdlib>
#include<ctime>

/*********** Declaration*******
 * I hereby certify that no part of this assignment has been copied from any other student’s work or fromany other source.
 * No part of the code has been written/produced for me by another person or copied from any other source.
I hold a copy of this assignment that I can produce if the original is lost or damaged.
 **************************/

int main()
{
    srand(time(0));
    NBGame game;
    game.play();
    game.printResults();
    return 0;
}