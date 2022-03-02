#include <algorithm>
#include "connectnboard.h"
#include "connectn_AI.h"

namespace ConnectN
{
    Node::Node(const Node& n)
    {
        this->board = n.board;
        this->column = n.column;
        this->weight = n.weight;
    }

    void Node::operator=(const Node& n)
    {
        this->board = n.board;
        this->column = n.column;
        this->weight = n.weight;
    }


    /**
     * 
     *
     */
    Solver::Solver(Board& b, Depth d): board(b), search_depth(d)
    {
    
    }


    /**
     *  
     *
     */
    grid_size_t Solver::move()
    {
        Node top = {Board(this->board), 0, neg_infinity};
        Node found = this->negamax(top, this->search_depth, neg_infinity, infinity, 1);
        return found.column;
    }


    /**
     * 
     *
     */
    Node Solver::negamax(Node node, Depth depth, Weight alpha, Weight beta, Weight color)
    {
        if (depth == 0 || board.win() == COMPUTER)
        {
            return (Node {node.board, node.column, color * node.weight});
        }
        std::vector<Node> children = enumerate_moves(node);
        order_moves(children);

        Node value = {node.board, node.column, neg_infinity};
        for (auto child : children)
        {
            value.weight = std::max(value.weight, -(negamax(child, depth - 1, -beta, -alpha, -color)).weight);
            alpha = std::max(value.weight, alpha);
            if (alpha >= beta)
            {
                break;
            }
        }
        return value;
    }

    std::vector<Node> Solver::enumerate_moves(Node node)
    {
        std::vector<Node> children;
        for (grid_size_t i = 0; i < node.board.size(); i++)
        {
            Node child = {Board(node.board), i, neg_infinity};
            child.board.add_at(i);
            child.weight = evaluate_move(node.board, child.board);
            children.push_back(child);
        }
        return children;
    }

    void Solver::order_moves(std::vector<Node>& children)
    {
        std::sort(children.begin(),
                  children.end(), 
                  [](Node first, Node second)
                      {
                          return (first.weight < second.weight);
                      });
    }

    Weight Solver::evaluate_move(Board& start, Board& moved)
    {
        return start.size() - moved.size();
    }
}
