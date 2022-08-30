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
                    al_draw_bitmap(this->red_marker, (j * 100),  (this->size() * 100) - (i * 100), 0);
                }
                else if (this->grid[i][j] == PLAYER2 || this->grid[i][j] == COMPUTER)
                {
                    al_draw_bitmap(this->yellow_marker, (j * 100), (this->size() * 100) - (i * 100), 0);
                }

                al_draw_bitmap(this->board_cell, (i * 100), (j+1) * 100, 0);
            }
        }
    }


    void GUIBoard::drop(Grid_Size x)
    {
        Grid_Size column = ((x / 100) >= this->grid.size()) ? this->grid.size() - 1 : x / 100;

        this->add_at(column);
    }

}
