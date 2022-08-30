#ifndef __CONNECTNBOARD_H__
#define __CONNECTNBOARD_H__ 1

#include <algorithm>
#include <iostream>
#include <string>
#include "boost/multi_array.hpp"

namespace ConnectN
{

    enum Player {NONE, PLAYER1, PLAYER2, COMPUTER};

    typedef boost::multi_array<Player, 2> Grid;
    typedef boost::multi_array_types::index Grid_Index;
    typedef boost::const_multi_array_ref<Player, 2, Player*>::size_type Grid_Size;

    std::string player_name(Player p);

    class Board
    {
    protected:
        Grid grid;
        uint8_t winning_count;
        Player player;
        bool useAI = false;

        uint8_t height();
        uint8_t column_top(Grid_Size column);
        void fill(Player player);
        Player scan_neighbors(Grid_Size row, Grid_Size column);

    public:
        Board();
        Board(uint8_t gs, uint8_t wc, Player p, bool ai = false);
        Board(const Board& b);

        void operator=(const Board& b);
        Grid_Size size();
        bool add_at(uint8_t column);
        void switch_player();
        Player current_player() {return this->player;}
        Player win();

        friend std::ostream& operator<<(std::ostream& os, const Board& b);
        friend class Solver;
    };
}

#endif
