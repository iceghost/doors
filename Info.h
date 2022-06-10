#ifndef INFO_H
#define INFO_H

#define PDC_WIDE
#include <curses.h>

#include <chrono>
#include <thread>

#include "Game.h"
#include "constants.h"

class Info {
    WINDOW* w;

   public:
    Info()
        : w(newwin(15, 50, PADDING,
                   2 * PADDING + Game::WIDTH * CELL_WIDTH + 1)) {}

    void print() {
        wattron(w, COLOR_PAIR(1) | A_BOLD);
        wprintw(w,
                "Open the doors, so that each room has\n"
                "a specific number of doors opened.\n\n"
                "Also, all rooms MUST be connected\n"
                "to each other.\n\n");
        wattroff(w, A_BOLD);
        wprintw(w,
                "Press ← ↑ → ↓ to move cursor\n"
                "Press Space to open doors\n"
                "Press Q to quit\n\n");
        wrefresh(w);
    }

    void printInfo() {
        wattron(w, COLOR_PAIR(2) | A_BOLD);
        wprintw(w, "you won, congratulations!\n");
        wattroff(w, COLOR_PAIR(2) | A_BOLD);
        wrefresh(w);
        std::this_thread::sleep_for(std::chrono::seconds(3));
        wprintw(w, "press any key to exit...\n");
        wrefresh(w);
    }
};

#endif