#include <algorithm>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "connectnboard.h"
#include "connectn_board_GUI.h"

namespace ConnectN
{
    void GUIBoard::draw()
    {
        for(Grid_Size i = 0; i < this->grid.size(); i++)
        {
            for(Grid_Size j = 1; j <= this->grid.size(); j++)
            {
                al_draw_bitmap(this->board_cell, (i * 100) + 50, j * 100, 0);
            }
        }
    }

}
