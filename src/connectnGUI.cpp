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
    display = al_create_display((100 * board_size) + 100, (100 * board_size) + 200);
    timer = al_create_timer(1.0 / 60.0);
    event_queue = al_create_event_queue();
    al_install_mouse();
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));


    ALLEGRO_MOUSE_STATE mstate;
    al_get_mouse_state(&mstate);
    ALLEGRO_BITMAP * marker[] = {
        al_load_bitmap("img/black_marker.png"),
        al_load_bitmap("img/red_marker.png"),
        al_load_bitmap("img/yellow_marker.png"),
        al_load_bitmap("img/yellow_marker.png")
    };

    ConnectN::GUIBoard board(display, board_size, winning_count, p, useAI);
    ConnectN::Solver AI(board, depth);


    board.draw();
    al_flip_display();
    al_start_timer(timer);

    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);

    bool running = true;
    while (running)
    {
        al_wait_for_event(event_queue, &event);
        switch(event.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
            {
                running = false;
                break;
            }

            // case ALLEGRO_EVENT_TIMER:
            // {
            //     al_clear_to_color(al_map_rgba(0, 0, 0, 0));
            //     board.draw();
            //     al_get_mouse_state(&mstate);
            //     if (al_mouse_button_down(&mstate, 1))
            //     {
            //         al_draw_bitmap(marker[p], event.mouse.x - board.token_midpoint(), event.mouse.y - board.token_midpoint(), 0);
            //     }
            //     al_flip_display();
            //     break;
            // }

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            {
                al_clear_to_color(al_map_rgba(0, 0, 0, 0));
                board.draw();
                al_draw_bitmap(marker[p], event.mouse.x - board.token_midpoint(), event.mouse.y - board.token_midpoint(), 0);
                al_flip_display();
                break;
            }

            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            {
                al_clear_to_color(al_map_rgba(0, 0, 0, 0));
                board.drop(event.mouse.x);
                board.draw();
                al_flip_display();
                p = board.switch_player();
                break;
            }
        }
        if (p == ConnectN::COMPUTER)
        {
            board.add_at(AI.move());
            board.draw();
            al_flip_display();
            p = board.switch_player();
        }
        ConnectN::Player winner = board.win();
        if (winner != ConnectN::NONE)
        {
            std::cout << ConnectN::player_name(winner) << " wins!" << std::endl;
            break;
        }
    }

    al_destroy_display(display);
    al_destroy_timer(timer);
    al_uninstall_keyboard();
    al_uninstall_mouse();
    al_shutdown_image_addon();

    for (int i = 0; i < 4; i++)
    {
        al_destroy_bitmap(marker[i]);
    }

    return 0;
}
