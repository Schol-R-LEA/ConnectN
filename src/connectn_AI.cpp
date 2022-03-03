#include <algorithm>
#include <chrono>
#include <random>
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
        Node top = {this->board, 0, neg_infinity};
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


    /**
     * 
     *
     */
    std::vector<Node> Solver::enumerate_moves(Node node)
    {
        std::vector<Node> children;
        for (grid_size_t i = 0; i < node.board.size(); i++)
        {
            Node child = {node.board, i, 0};
            if (!child.board.add_at(i))
            {
                continue;
            }
            child.weight = evaluate_move(child);
            children.push_back(child);
        }
        return children;
    }


    /**
     * 
     *
     */
    void Solver::order_moves(std::vector<Node>& children)
    {
        std::sort(children.begin(),
                  children.end(), 
                  [](Node first, Node second)
                      {
                          return (first.weight < second.weight);
                      });
    }


    /**
     * 
     *
     */
    Weight Solver::evaluate_move(Node& node)
    { 
        grid_size_t size = node.board.size();
        Player player = node.board.current_player();
        Weight weight = 0;
        grid_size_t column = node.column;

        // add weight depending on whether the token is on the 
        // center column(s).
        if (size % 2)
        {
            if (node.column == std::ceil(size/2))
            {
                weight += 4; 
            } 
        }
        else
        { 
            // if there are two central columns, weight slightly
            // less than if there is only one
            if (column == (size/2) || column == (size/2)+1)
            {
                weight += 3; 
            }
        }
        
        if (player == node.board.win())
        {
            weight += 1000;
        }
        weight += evaluate_column(node);
        return weight;
    }


   /**
     * Weight Solver::evaluate_column(Node& n)
     * - scan the neighboring square of a given square to see if there 
     *   is a winning sequence.
     * @param node - version of board to evaluate
     */
    Weight Solver::evaluate_column(Node& n)
    {
        Weight weight = n.board.size() - n.board.size();
        

        return weight;
    }

}
