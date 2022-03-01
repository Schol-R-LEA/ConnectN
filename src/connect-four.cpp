#include <iostream>
#include "connectnboard.h"


/**
 * main driver
 */
int main()
{
    ConnectNBoard board(7, 4, PLAYER1);
    std::cout << board;
    
    return 0;
}
