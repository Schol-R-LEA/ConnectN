#ifndef __BOARD_H__
#define __BOARD_H__ 1

#include <algorithm>
#include <iostream>
#include <vector>



enum SquareState {EMPTY, PLAYER, COMPUTER};
enum PlayOrder {PLAYER, COMPUTER};


class ConnectNBoard
{
public:
    ConnectNBoard(uint8_t gs, uint8_t wc, PlayOrder f);

private:
    uint8_t grid_size, winning_count;
    PlayOrder firstPlayer;
    vector<vector<SquareState> > grid;


};

#endif
