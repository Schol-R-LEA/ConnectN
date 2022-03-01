#ifndef __BOARD_H__
#define __BOARD_H__ 1

#include <algorithm>
#include <iostream>
#include <string>
#include "boost/multi_array.hpp"

enum Player {NONE, PLAYER1, PLAYER2};

typedef boost::multi_array<Player, 2> grid_t;
typedef boost::multi_array_types::index grid_index;
typedef boost::const_multi_array_ref<Player, 2, Player*>::size_type grid_size_t;

std::string player_name(Player p);

class ConnectNBoard
{
private:
    grid_t grid;
    uint8_t winning_count;
    Player player;

    uint8_t height();
    void fill(Player player);
    void switch_player();
    Player scan_neighbors(grid_size_t row, grid_size_t column);

public:
    ConnectNBoard();
    ConnectNBoard(uint8_t gs, uint8_t wc, Player p);
    ConnectNBoard(const ConnectNBoard& b);

    grid_size_t dim();
    bool add_at(uint8_t column);
    Player win();

    friend std::ostream& operator<<(std::ostream& os, const ConnectNBoard& b);
};


#endif
