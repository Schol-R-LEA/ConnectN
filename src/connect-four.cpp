#include <iostream>
#include "connectnboard.h"
#include "connectn_AI.h"

int main(int argc, char* argv[])
{
    ConnectN::grid_size_t board_size = 7, winning_count = 4;
    ConnectN::Player p = ConnectN::PLAYER1;
    ConnectN::Depth depth = 5;

    switch (argc)
    {
    case 5:
        depth = std::stoi(argv[4]);
        [[fallthrough]];
    case 4:
        if (std::stoi(argv[3]) == 2)
        {
            p = ConnectN::PLAYER2;
        }
        if (std::stoi(argv[3]) == 3)
        {
            p = ConnectN::COMPUTER;
        }
        [[fallthrough]];
    case 3:
        winning_count = std::min(std::stoi(argv[2]), 10);
        [[fallthrough]];
    case 2:
        board_size =  std::min(std::stoi(argv[1]), 20);
        [[fallthrough]];
    default:
        break;
    }

    ConnectN::Board board(board_size, winning_count, p);
    ConnectN::Solver computer(board, depth);

    ConnectN::Player winner = ConnectN::NONE;
    while(true)
    {
        ConnectN::grid_size_t next_column = 0;

        if (board.current_player() == ConnectN::COMPUTER)
        {
            while (!board.add_at(computer.move()))
            {
            }
        }
        else
        {
            do 
            {
                std::cout << ConnectN::player_name(board.current_player()) << " enter a column: ";
                std::cin >> next_column;
            } 
            while (!board.add_at(next_column));
        }
        std::cout << board;
        winner = board.win();
        if (winner != ConnectN::NONE)
        {
            std::cout << ConnectN::player_name(winner) << " wins!"<< std::endl;
            break;
        }
        board.switch_player();
    }

    return 0;
}
