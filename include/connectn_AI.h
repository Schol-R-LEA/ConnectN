#ifndef __CONNECTN_AI_H__
#define __CONNECTN_AI_H__ 1

#include <vector>
#include "connectnboard.h"

namespace ConnectN
{

    typedef intmax_t Weight;
    typedef uint8_t Depth;
    const Weight infinity = INTMAX_MAX, neg_infinity = INTMAX_MIN;

    struct Node
    {
        Board board;
        grid_size_t column;
        Weight weight;
        Node(const Board& b, grid_size_t c, Weight w): board(b), column(c), weight(w) {};
        Node(const Node& n);
        void operator=(const Node& n);
    }; 


    class Solver
    {
    private:
        Board& board;
        Depth search_depth;
        Node negamax(Node node, Depth depth, Weight alpha, Weight beta, Weight color);
        std::vector<Node> enumerate_moves(Node node);
        void order_moves(std::vector<Node>& children);
        Weight evaluate_move(Node& node);
        Weight evaluate_column(Node& node);

    public:
        Solver(Board& b, Depth d);
        grid_size_t move();

        friend class Board;
    };
}

#endif
