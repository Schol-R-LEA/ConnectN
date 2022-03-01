#include <iostream>
#include "connectnboard.h"

using namespace ConnectN;


void check_win(Board& board)
{
    Player p = board.win();
    if (p != NONE)
    {
        std::cout << player_name(p) << " wins!"<< std::endl;
        exit(0);
    }
}

int main()
{
    Board board;
    std::cout << board;
    bool success = board.add_at(0);
    if (success)
    {
        std::cout << board;
        check_win(board);
    }
    else 
    {
        std::cout << "Could not add counter" << std::endl;
        return 0;
    }

    success = board.add_at(1);
    if (success)
    {
        std::cout << board;
        check_win(board);
    }
    else 
    {
        std::cout << "Could not add counter" << std::endl;
        return 0;
    }

    success = board.add_at(1);
    if (success)
    {
        std::cout << board;
        check_win(board);
    }
    else 
    {
        std::cout << "Could not add counter" << std::endl;
        return 0;
    }
    board.switch_player();


    success = board.add_at(2);
    if (success)
    {
        std::cout << board;
        check_win(board);
    }
    else 
    {
        std::cout << "Could not add counter" << std::endl;
        return 0;
    }
    board.switch_player();

    success = board.add_at(2);
    if (success)
    {
        std::cout << board;
        check_win(board);
    }
    else 
    {
        std::cout << "Could not add counter" << std::endl;
        return 0;
    }
    board.switch_player();

    success = board.add_at(1);
    if (success)
    {
        std::cout << board;
        check_win(board);
    }
    else 
    {
        std::cout << "Could not add counter" << std::endl;
        return 0;
    }
    board.switch_player();

    success = board.add_at(2);
    if (success)
    {
        std::cout << board;
        check_win(board);
    }
    else 
    {
        std::cout << "Could not add counter" << std::endl;
        return 0;
    }
    board.switch_player();

    success = board.add_at(3);
    if (success)
    {
        std::cout << board;
        check_win(board);
    }
    else 
    {
        std::cout << "Could not add counter" << std::endl;
        return 0;
    }
    board.switch_player();

    success = board.add_at(3);
    if (success)
    {
        std::cout << board;
        check_win(board);
    }
    else 
    {
        std::cout << "Could not add counter" << std::endl;
        return 0;
    }
    board.switch_player();

    success = board.add_at(3);
    if (success)
    {
        std::cout << board;
        check_win(board);
    }
    else 
    {
        std::cout << "Could not add counter" << std::endl;
        return 0;
    }
    board.switch_player();

    success = board.add_at(1);
    if (success)
    {
        std::cout << board;
        check_win(board);
    }
    else 
    {
        std::cout << "Could not add counter" << std::endl;
        return 0;
    }
    board.switch_player();

    success = board.add_at(0);
    if (success)
    {
        std::cout << board;
        check_win(board);
    }
    else 
    {
        std::cout << "Could not add counter" << std::endl;
        return 0;
    }
    board.switch_player();

    success = board.add_at(4);
    if (success)
    {
        std::cout << board;
        check_win(board);
    }
    else 
    {
        std::cout << "Could not add counter" << std::endl;
        return 0;
    }

    return 0; 
}
