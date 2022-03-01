#include <iostream>
#include "connectnboard.h"
#include "connectn_AI.h"

int main(int argc, char* argv[])
{
    grid_size_t board_size = 7, winning_count = 4;
    Player p = PLAYER1;

    switch (argc)
    {
    case 4:
        if (std::stoi(argv[3]) == 2)
        {
            p = PLAYER2;
        }
        if (std::stoi(argv[3]) == 3)
        {
            p = COMPUTER;
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

    ConnectNBoard board(board_size, winning_count, p);
    ConnectN_AI computer(board);

    Player winner = NONE;
    while(true)
    {
        grid_size_t next_column = 0;

        if (board.current_player() == COMPUTER)
        {
            while (!board.add_at(computer.move()))
            {
            }
        }
        else
        {
            do 
            {
                std::cout << player_name(board.current_player()) << " enter a column: ";
                std::cin >> next_column;
            } 
            while (!board.add_at(next_column));
        }
        std::cout << board;
        winner = board.win();
        if (winner != NONE)
        {
            std::cout << player_name(winner) << " wins!"<< std::endl;
            break;
        }
        board.switch_player();
    }

    return 0;
}
