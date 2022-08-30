#include <algorithm>
#include <chrono>
#include <cmath>
#include <random>
#include "connectnboard.h"
#include "connectn_AI.h"

namespace ConnectN
{

    /**
     * 
     *
     */
    Node::Node(const Node& n)
    {
        this->board = n.board;
        this->column = n.column;
        this->weight = n.weight;
        this->depth = n.depth;
    }


    /**
     * 
     *
     */
    void Node::operator=(const Node& n)
    {
        this->board = n.board;
        this->column = n.column;
        this->weight = n.weight;
        this->depth = n.depth;
    }


    /**
     * 
     *
     */
    Solver::Solver(Board& b, Depth d = 3): board(b), search_depth(d)
    {
    
    }


    /**
     *  
     *
     */
    Grid_Size Solver::move()
    {
        Node top = {this->board, 0, neg_infinity, this->search_depth};
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
            return (Node {node.board, node.column, color * node.weight, depth});
        }
        std::vector<Node> children = enumerate_moves(node);

        order_moves(children);
        Node value = {node.board, node.column, neg_infinity, depth};

        for (auto child : children)
        {
            value.column = child.column;
            Node recursive_value = negamax(child, depth - 1, -beta, -alpha, -color);
            value.weight = std::max(value.weight, -recursive_value.weight);
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
        for (Grid_Size i = 0; i < node.board.size(); i++)
        {
            Node child = {node.board, i, 0, static_cast<Depth>(node.depth-1)};
            if (!child.board.add_at(i))
            {
                continue;
            }
            if (child.depth != this->search_depth)
            {
                child.board.switch_player();
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
        Grid_Size size = node.board.size();
        Weight weight = 0;
        Grid_Size column = node.column;
        Grid_Size midpoint = std::ceil(size/2);

        // add weight depending on whether the token is on the 
        // center column(s).
        if (size % 2)
        {
            if (node.column == midpoint)
            {
                weight += 4; 
            } 
        }
        else
        { 
            // if there are two central columns, weight half as much
            // as you would if there is only one
            if (column == midpoint-1 || column == midpoint)
            {
                weight += 2; 
            }
        }

        weight += evaluate_node(node);
        return weight;
    }

    /**
     * Weight Solver::weight_column(Grid_Size c) - 
     * @param c - total number of 
     */
    Weight Solver::weight_column(Grid_Size c)
    {
        Weight weight = 0;
        Grid_Size max = this->board.winning_count;
        Grid_Size midpoint = std::floor(max/2);

        if (c >= this->board.winning_count)
        {
            // winning move, weight it the maximum amount
            weight = 1000;
        }
        else
        {
            // for every token beyond half the winning amount,
            // increase the weighting by 2
            Weight weighted_count = c - midpoint;
            weight = std::max(0, static_cast<int>(weighted_count+1)) * 2;
        }

        return weight;
    }
        
    /**
     * Weight Solver::evaluate_column(Node& node)
     * - scan the neighboring square of a given square to see if there 
     *   is a winning sequence.
     * @param node - version of board to evaluate
     */
    Weight Solver::evaluate_node(Node& node)
    {
        Weight weight = 0;
        Player p = node.board.current_player();
        Grid_Size size = node.board.size();    
        Grid_Size offset = node.board.winning_count, 
            target = static_cast<Grid_Size>(node.board.winning_count - 1),
            row = std::max(0, node.board.column_top(node.column) - 1),
            column = node.column;

        bool check_up = (row < (size - target)),
            check_left = (column > offset), 
            check_right = (column < (size - offset));

        if (check_right)
        {
            Grid_Size count = 1;
            for (Grid_Size c = column; c < std::min(size, column + offset) && (node.board.grid[row][c] == p); c++, count++)
            {
                // iterate through
            }
            weight += weight_column(count); 
        }

        if (check_up)
        {
            Grid_Size count = 1;

            for (Grid_Size r = row; (r < std::min(size, row + offset)) && (node.board.grid[r][column] == p); r++, count++)
            {
                // iterate through
            }
            weight += weight_column(count);
        }

        if (check_left)
        {
            Grid_Size count = 1;
            for (Grid_Size r = row, c = column, count = 0; 
                 (r < (row + offset)) && (c >= (column - target)) && (node.board.grid[r][c] == p); 
                 r++, c--, count++)
            {
                // iterate through
            }
            weight += weight_column(count);
        }
 
        if (check_right)
        {
            Grid_Size count = 1;
            for (Grid_Size r = row, c = column, count = 0; 
                 (r < std::min(size, row + offset)) && (c < std::min(size, column + offset)) && (node.board.grid[r][c] == p); 
                 r++, c++, count++)
            {
                // iterate through
            }
            weight += weight_column(count);
        }
 
        return weight;
    }

}
