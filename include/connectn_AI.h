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
        Grid_Size column;
        Weight weight;
        Depth depth;
        Node(const Board& b, Grid_Size c, Weight w, Depth d): board(b), column(c), weight(w), depth(d) {};
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
        Weight evaluate_node(Node& node);
        Weight weight_column(Grid_Size c);

    public:
        Solver(Board& b, Depth d);
        Grid_Size move();

        friend class Board;
    };
}

#endif
