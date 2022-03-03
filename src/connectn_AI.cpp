#include <algorithm>
#include <chrono>
#include <cmath>
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
            Node recursive_value = negamax(child, depth - 1, -beta, -alpha, -color);
            std::cout << "Current value " << value.weight << std::endl;
            std::cout << "Recursive value " << recursive_value.weight << std::endl;
            value.weight = std::max(value.weight, -recursive_value.weight);
            if (value.weight == child.weight)
            {
                value.column = child.column;
            }
            alpha = std::max(value.weight, alpha);
            if (alpha >= beta)
            {
                break;
            }
        }
        
        std::cout << "Final column: " << value.column << " of weight: " << value.weight << std::endl;
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
            child.board.switch_player();
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
        // Player player = node.board.current_player();
        Weight weight = 0;
        grid_size_t column = node.column;

        // add weight depending on whether the token is on the 
        // center column(s).
        if (size % 2)
        {
            if (node.column == std::ceil(size/2))
            {
                weight += 10; 
            } 
        }
        else
        { 
            // if there are two central columns, weight half as much
            // as you would if there is only one
            if (column == (size/2) || column == (size/2)+1)
            {
                weight += 5; 
            }
        }
        
        weight += evaluate_node(node);
        return weight;
    }

    /**
     * Weight Solver::weight_column(Node& n)
     * - scan the neighboring square of a given square to see if there 
     *   is a winning sequence.
     * @param c - total number of 
     */
    Weight Solver::weight_column(grid_size_t c)
    {
        Weight weight = 0;
        grid_size_t max = this->board.winning_count;

        if (c >= this->board.winning_count)
        {
            // winning move, weight it the maximum amount
            weight = 1000;
        }
        else
        {
            // for every token beyond half the winning amount,
            // increase the weighting by 2 
            weight = std::max(0, static_cast<int>((c - std::ceil(max/2)) * 2)); 
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
        grid_size_t size = node.board.size();    
        grid_size_t offset = node.board.winning_count, 
            target = static_cast<grid_size_t>(node.board.winning_count-1),
            row = node.board.column_height(node.column),
            column = node.column;

        bool check_up = (row < (size - target)),
            check_left = (column > target-1), 
            check_right = (column < (size - target));

        if (check_right)
        {
            std::cout << "Right" << std::endl;
            grid_size_t count = 0;
            for (grid_size_t c = column, count = 0; c < std::min(size, column + offset) && (node.board.grid[row][c] == p); c++, count++)
            {
                // iterate through
                std::cout << c << " ";
            }
            if (count > 0)
                std::cout << "Right Count:" << count << std::endl;
            weight += weight_column(count); 
        }

        if (check_up)
        {
            std::cout << "up" << std::endl;
            grid_size_t count = 0;
            for (grid_size_t r = row; (r < std::min(size, row + offset)) && (node.board.grid[r][column] == p); r++, count++)
            {
                // iterate through
                std::cout << r << " ";
            }
            if (count > 0)
                std::cout << "Up Count: " << count << std::endl;
            weight += weight_column(count);
        }

        if (check_left)
        {
            std::cout << "up left" << std::endl;
            grid_size_t count = 0;
            for (grid_size_t r = row, c = column, count = 0; 
                 (r < (row + offset)) && (c >= (column - target)) && (node.board.grid[r][c] == p); 
                 r++, c--, count++)
            {
                // iterate through
                std::cout << "[ " << r << "," << c << "]";
            }
            if (count > 0)
                std::cout << "up Left Count: " << count << std::endl;
            weight += weight_column(count);
        }
 
        if (check_right)
        {
            std::cout << "up right" << std::endl;
            grid_size_t count = 0;
            for (grid_size_t r = row, c = column, count = 0; 
                 (r < std::min(size, row + offset)) && (c < std::min(size, column + offset)) && (node.board.grid[r][c] == p); 
                 r++, c++, count++)
            {
                std::cout << "[ " << r << "," << c << "] ";
            }
            if (count > 0)
                std::cout << "Up Right Count: " << count << std::endl;
            weight += weight_column(count);
        }

        std::cout << "Evaluated Weight: " << weight << std::endl; 
        return weight;
    }

}
