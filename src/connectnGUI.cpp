#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "connectnboard.h"
#include "connectn_board_GUI.h"
#include "connectn_AI.h"

int main(int argc, char* argv[])
{
    ConnectN::Grid_Size board_size = 7, winning_count = 4;
    ConnectN::Player p = ConnectN::PLAYER1;
    bool useAI = false;
    ConnectN::Depth depth = 4;

    switch (argc)
    {
    case 6:
        depth = std::stoi(argv[5]);
        [[fallthrough]];
    case 5:
        if (std::stoi(argv[4]) == 2)
        {
            p = ConnectN::PLAYER2;
        }
        [[fallthrough]];
    case 4:
        if (std::stoi(argv[3]) == 1)
        {
            useAI = true;
            if (p == ConnectN::PLAYER2)
            {
                p = ConnectN::COMPUTER;
            }
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


    ALLEGRO_DISPLAY * display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer;

    al_init();
    al_init_image_addon();
    display = al_create_display(100 * board_size + 100, 100 * board_size + 200);
    timer = al_create_timer(1.0 / 60.0);
    event_queue = al_create_event_queue();
    al_install_keyboard();
    al_install_mouse();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));


    ALLEGRO_MOUSE_STATE mstate;
    al_get_mouse_state(&mstate);
    ALLEGRO_BITMAP * player1_marker = al_load_bitmap("img/red_marker.png");

    ConnectN::GUIBoard board(display, board_size, winning_count, p, useAI);
    ConnectN::Solver AI(board, depth);


    board.draw();
    al_flip_display();


    bool running = true;
    while (running)
    {

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        switch(event.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
            {
                running = false;
                break;
            }
            case ALLEGRO_EVENT_MOUSE_AXES:
            {
                if (mstate.buttons & 1)
                {
                    board.draw();

                    al_draw_bitmap(player1_marker, event.mouse.x, event.mouse.y, 0);
                    al_flip_display();
                }
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            {
                board.draw();
                al_draw_bitmap(player1_marker, event.mouse.x, event.mouse.y, 0);
                al_flip_display();
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            {

                break;
            }
        }
    }

    al_destroy_display(display);
    al_destroy_timer(timer);
    al_uninstall_keyboard();
    al_uninstall_mouse();
    al_shutdown_image_addon();

    return 0;
}
