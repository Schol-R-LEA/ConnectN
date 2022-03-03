#include <algorithm>
#include <iostream>
#include <string>
#include "connectnboard.h"


namespace ConnectN
{
    /**
     * Board::Board() - default constructor
     */
    Board::Board(): grid(boost::extents[7][7]), winning_count(4), player(PLAYER1)
    {
        // classic Connect-4 grid
        useAI = true;
        this->fill(NONE);
    }


    /**
     * Board::Board(uint8_t gs, uint8_t wc, Player p) - standard c'tor
     * @param gs - grid size
     * @param wc - number of tokens need to win
     * @param p  - first player 
     */
    Board::Board(uint8_t gs, uint8_t wc, Player p): grid(boost::extents[gs][gs]), winning_count(std::min(gs, wc)), player(p)
    {
        useAI = (this->player == COMPUTER);
        this->fill(NONE);
    }


    /**
     * Board::Board(const Board& b) - copy c'tor 
     * @param b - Board objects to copy
     */
    Board::Board(const Board& b): grid(boost::extents[b.grid.size()][b.grid.size()]), 
                                                          winning_count(b.winning_count), 
                                                          player(b.player)
    {
        for (grid_size_t r = 0; r < b.grid.size(); r++)
        {
            for (grid_size_t c = 0; c < b.grid.size(); c++)
            {
                this->grid[r][c] = b.grid[r][c];
            }
        }
    }


    /**
     * grid_size_t Board::size() - dimensions of the board
     */
    grid_size_t Board::size()
    {
        return this->grid.size();
    }


    /**
     * uint8_t Board::height() - highest column on the board
     */
    uint8_t Board::height()
    {
        uint8_t h = 0;

        for (auto row: this->grid)
        {
            bool row_empty = true; 
            for (auto column: row)
            {
                if (column != NONE)
                {
                    h++;
                    row_empty = false;
                    break;
                }
            }
            if (row_empty)
            {
                break;
            }
        }
        return std::min(h, static_cast<uint8_t>(this->size()));
    }


    /**
     * void Board::switch_player() - change the current player
     */
    void Board::switch_player()
    {
        this->player = ((this->player == PLAYER1) 
                        ? ((this->useAI) 
                           ? COMPUTER 
                           : PLAYER2)
                        : PLAYER1);
    }


    /**
     * bool Board::add_at(uint8_t column) - add a token to a column
     * @param column - column to add the token to
     */
    bool Board::add_at(uint8_t column)
    {
        if (column < this->size())
        {
            for (grid_size_t row = 0; row < this->size(); row++)
            {
                if (this->grid[row][column] == NONE)
                {
                    this->grid[row][column] = this->player;
                    return true;
                }
            }
        }
        return false;
    }


    /**
     * Player Board::win() - return which player has won, if any
     */
    Player Board::win()
    {
        for (grid_size_t row = 0; row < this->height(); row++)
        {
            for (grid_size_t column = 0; column < this->size(); column++)
            {
                Player p = this->scan_neighbors(row, column);
                if (p != NONE)
                {
                    return p;
                }
            }
        }
        return NONE;
    }


    /**
     * Player Board::scan_neighbors(grid_size_t row, grid_size_t column)
     * - scan the neighboring square of a given square to see if there 
     *   is a winning sequence.
     * @param row    - row of square to scan from
     * @param column - column of square to scan from
     */
    Player Board::scan_neighbors(grid_size_t row, grid_size_t column)
    {
        Player p = this->grid[row][column];
        grid_size_t offset = this->winning_count,  target = static_cast<grid_size_t>(this->winning_count-1);
        if (p == NONE)
        {
            return NONE;
        }

        bool check_up = (row < (this->size() - target)),
            check_down = (row > target),
            check_left = (column > target-1), 
            check_right = (column < (this->size() - target));

        if (check_up)
        {
            for (grid_size_t r = row, count = 0; (r < (row + offset)) && (this->grid[r][column] == p); r++, count++)
            {
                if (count == target)
                {
                    return p;
                }
            }
        }

        if (check_down)
        {
            for (grid_size_t r = row, count = 0; r < (row - offset + 1) && (this->grid[r][column] == p); r--, count++)
            {
                if (count == target)
                {
                    return p;
                }
            }
        }

        if (check_left)
        {
            for (grid_size_t c = column, count = 0; c > (column - offset) && (this->grid[row][c] == p); c--, count++)
            {
                if (count == target)
                {
                    return p;
                }
            }
            if (check_up)
            {
                for (grid_size_t r = row, c = column, count = 0; 
                     (r < (row + offset)) && (c >= (column - target)) && (this->grid[r][c] == p); 
                     r++, c--, count++)
                {
                    if (count == target)
                    {
                        return p;
                    }
                }
            }
            if (check_down)
            {
                for (grid_size_t r = row, c = column, count = 0; 
                     (r > (row - offset + 1)) && (c > (column - offset)) && (this->grid[r][c] == p); 
                     r--, c--, count++)
                {
                    if (count == target)
                    {
                        return p;
                    }
                }
            }
        }

        if (check_right)
        {
            for (grid_size_t c = column, count = 0; c < (column + offset) && (this->grid[row][c] == p); c++, count++)
            {
                if (count == target)
                {
                    return p;
                }
            }

            if (check_up)
            {
                for (grid_size_t r = row, c = column, count = 0; 
                     (r < (row + offset)) && (c < (column + offset)) && (this->grid[r][c] == p); 
                     r++, c++, count++)
                {
                    if (count == target)
                    {
                        return p;
                    }
                }
            }

            if (check_down)
            {      
                for (grid_size_t r = row, c = column, count = 0; 
                     (r >= (row - offset + 1)) && (c < (column + offset)) && (this->grid[r][c] == p); 
                     r--, c++, count++)
                {
                    if (count == target)
                    {
                        return p;
                    }
                }
            }  
        }
        return NONE;
    }


    /**
     * void Board::fill(Player player) - fill the board with a given value
     * @param player - player calue to fill the board with
     */
    void Board::fill(Player player) 
    {
        for (grid_size_t i = 0; i < this->grid.size(); i++)
        {
            for (grid_size_t j = 0; j < this->grid.size(); j++)
            {
                this->grid[i][j] = player;
            }
        }
    }


    /**
     * std::ostream& operator<<(std::ostream& os, const Board& b)
     * @param os - output stream to write to
     * @param b - Board to print
     */
    std::ostream& operator<<(std::ostream& os, const Board& b)
    {
        std::string border;

        border.resize((b.grid.size() * 2)-1, '-');
        os << ' ' << border << std::endl;
        for (grid_size_t r = b.grid.size(); r > 0; r--) 
        {
            for (grid_size_t c = 0; c < b.grid.size(); c++) 
            {
                os << "|";
                switch (b.grid[r-1][c]) 
                {
                case NONE: 
                    os << ' '; 
                    break; // no piece
                case PLAYER1:
                    os << 'O'; 
                    break; // player one's piece
                case PLAYER2:
                    [[fallthrough]];
                case COMPUTER:
                    os << 'X'; 
                    break; // player two's or Computer's piece
                }
                if (c + 1 == b.grid.size()) { os << "|"; }
            }
            os << std::endl;
        }
        os << ' ' << border << std::endl;
        os << std::endl;
        return os;
    }


    /**
     * void Board::operator=(const Board& b)
     * @param b - Board to copy 
     */
void Board::operator=(const Board& b)
{
    for (grid_size_t r = 0; r < b.grid.size(); r++)
    {
        for (grid_size_t c = 0; c < b.grid.size(); c++)
        {
            this->grid[r][c] = b.grid[r][c];
        }
    }
    this->winning_count = b.winning_count;
    this->player = b.player;
    this->useAI = b.useAI;
}


    /**
     * std::string player_name(Player p) - map a Player value to a representative string
     * @param p - Player value to map
     */
    std::string player_name(Player p) 
    {
        return ((p == NONE) 
                ? "No one"
                : ((p == PLAYER1) 
                   ? "Player one" 
                   : ((p == PLAYER2) 
                      ? "Player two" 
                      : "Computer")));
    }
}
