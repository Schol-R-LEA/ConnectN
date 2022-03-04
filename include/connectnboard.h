#ifndef __CONNECTNBOARD_H__
#define __CONNECTNBOARD_H__ 1

#include <algorithm>
#include <iostream>
#include <string>
#include "boost/multi_array.hpp"

namespace ConnectN
{

    enum Player {NONE, PLAYER1, PLAYER2, COMPUTER};

    typedef boost::multi_array<Player, 2> grid_t;
    typedef boost::multi_array_types::index grid_index;
    typedef boost::const_multi_array_ref<Player, 2, Player*>::size_type grid_size_t;

    std::string player_name(Player p);

    class Board
    {
    private:
        grid_t grid;
        uint8_t winning_count;
        Player player;
        bool useAI = false;

        uint8_t height();
        uint8_t column_top(grid_size_t column);
        void fill(Player player);
        Player scan_neighbors(grid_size_t row, grid_size_t column);

    public:
        Board();
        Board(uint8_t gs, uint8_t wc, Player p);
        Board(const Board& b);

        void operator=(const Board& b);
        grid_size_t size();
        bool add_at(uint8_t column);
        void switch_player();
        Player current_player() {return this->player;}
        Player win();

        friend std::ostream& operator<<(std::ostream& os, const Board& b);
        friend class Solver;
    };
}

#endif
