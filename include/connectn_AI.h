#ifndef __CONNECTN_AI_H__
#define __CONNECTN_AI_H__ 1

#include "connectnboard.h"

namespace ConnectN
{

    typedef intmax_t weight;
    const weight infinity = INTMAX_MAX, neg_infinity = INTMAX_MIN;


    class Solver
    {
    private:
        Board& board;
       // weight minimax(node, uint32_t depth, bool maximizing_player);

    public:
        Solver(Board& b);
        grid_size_t move();

        friend class Board;
    };
}

#endif
