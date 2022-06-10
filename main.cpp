#define PDC_WIDE
#include <curses.h>
#include <panel.h>
#include <windows.h>

#include <array>
#include <iostream>
#include <string>

#include "Cell.h"
#include "Game.h"
#include "Info.h"

int main() {
    int ch;

    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);

    Cell::init_cchars();
    Game* game = Game::generate(time(nullptr));
    Info info;
    game->print();
    info.print();

    auto game_over = false;
    while (!game_over) {
        int ch = getch();
        switch (ch) {
            case 'q':
                game_over = true;
                break;
            case KEY_LEFT:
                game->move_cursor_left();
                break;
            case KEY_RIGHT:
                game->move_cursor_right();
                break;
            case KEY_DOWN:
                game->move_cursor_down();
                break;
            case KEY_UP:
                game->move_cursor_up();
                break;
            case ' ':
                game->toggle_door();
                break;
        };
        if (game->fulfilled()) {
            info.printInfo();
            game_over = true;
        }
    }
    getch();
    endwin();
    return 0;
}
