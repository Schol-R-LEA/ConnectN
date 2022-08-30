#ifndef __CONNECTN_BOARD_GUI_H__
#define __CONNECTN_BOARD_GUI_H__ 1

#include "connectnboard.h"

namespace ConnectN
{
    class GUIBoard : public Board
    {
    private:
        ALLEGRO_DISPLAY *display;
        ALLEGRO_BITMAP *board_cell;
        ALLEGRO_BITMAP *red_marker, *yellow_marker;

    public:
        GUIBoard(ALLEGRO_DISPLAY *d): Board(),
                                      display(d),
                                      board_cell(al_load_bitmap("img/board_cell.png")),
                                      red_marker(al_load_bitmap("img/red_marker.png")),
                                      yellow_marker(al_load_bitmap("img/yellow_marker.png"))
        {};

        GUIBoard(ALLEGRO_DISPLAY *d, uint8_t gs, uint8_t wc, Player p, bool ai = false): Board(gs, wc, p, ai),
                                                                                         display(d),
                                                                                         board_cell(al_load_bitmap("img/board_cell.png")),
                                                                                         red_marker(al_load_bitmap("img/red_marker.png")),
                                                                                         yellow_marker(al_load_bitmap("img/yellow_marker.png"))
        {};

        GUIBoard(const GUIBoard& b): Board(b),
                                     display(b.display),
                                     board_cell(al_load_bitmap("img/board_cell.png")),
                                     red_marker(al_load_bitmap("img/red_marker.png")),
                                     yellow_marker(al_load_bitmap("img/yellow_marker.png"))
        {};

        void draw();
        void drop(Grid_Size x);

        friend class Solver;
    };
}

#endif
