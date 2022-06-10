#ifndef CELL_H
#define CELL_H

#define PDC_WIDE
#include <curses.h>

#include "constants.h"

class Cell {
    WINDOW* w;
    int x, y;
    int value;
    bool top = false, bottom = false, left = false, right = false;

    static cchar_t CORNER;
    static cchar_t VLINE;
    static cchar_t HLINE;
    static cchar_t OPEN;

   public:
    static void init_cchars();

    Cell() = default;
    Cell(int y, int x, int value)
        : w(newwin(CELL_HEIGHT, CELL_WIDTH, PADDING + y * (CELL_HEIGHT - 1),
                   PADDING + x * (CELL_WIDTH - 1))),
          value(value),
          x(x),
          y(y) {}

    void update();

    void update_top(bool top);
    void update_bottom(bool bottom);
    void update_left(bool left);
    void update_right(bool right);
    bool get_top();
    bool get_bottom();
    bool get_left();
    bool get_right();
    bool fulfiled();
    int get_x() { return x; }
    int get_y() { return y; }
};

#endif