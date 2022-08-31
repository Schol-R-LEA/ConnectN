#include <algorithm>
#include <cstdint>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "connectnboard.h"
#include "connectn_board_GUI.h"

namespace ConnectN
{
    void GUIBoard::draw()
    {
        for(Grid_Size i = 0; i < this->size(); i++)
        {
            for(Grid_Size j = 0; j < this->size(); j++)
            {
                if (this->grid[i][j] == PLAYER1)
                {
                    al_draw_bitmap(this->red_marker, (j * this->token_size()),  (this->size() * this->token_size()) - (i * this->token_size()), 0);
                }
                else if (this->grid[i][j] == PLAYER2 || this->grid[i][j] == COMPUTER)
                {
                    al_draw_bitmap(this->yellow_marker, (j * this->token_size()), (this->size() * this->token_size()) - (i * this->token_size()), 0);
                }

                al_draw_bitmap(this->board_cell, (i * this->token_size()), (j+1) * this->token_size(), 0);
            }
        }
    }


    void GUIBoard::drop(Grid_Size x)
    {
        Grid_Size column = ((x / this->token_size()) >= this->grid.size()) ? this->grid.size() - 1 : x / this->token_size();

        this->add_at(column);
    }

}
