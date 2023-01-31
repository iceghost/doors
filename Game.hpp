#ifndef GAME_H
#define GAME_H

#define PDC_WIDE
#include <curses.h>

#include <array>
#include <string>

#include "Cell.h"

class Game {
   public:
    static const size_t HEIGHT = 5;
    static const size_t WIDTH = 5;

   private:
    std::array<std::array<Cell, WIDTH>, HEIGHT> cellss;

    int hx = 0, hy = 0;
    int vx = 0, vy = 0;
    bool is_vertical = true;

    std::array<std::array<bool, WIDTH - 1>, HEIGHT> v_doorss = {};
    std::array<std::array<bool, WIDTH>, HEIGHT - 1> h_doorss = {};

    Game(std::array<std::array<int, Game::WIDTH>, Game::HEIGHT> vals);

   public:
    void move_cursor_left();
    void move_cursor_right();
    void move_cursor_up();
    void move_cursor_down();

    std::pair<int, int> get_pos();

    void update_cursor();

    void toggle_door();

    void print();

    bool fulfilled();

    static Game* generate(unsigned int seed);

   private:
    int fulfilledHelp(
        int x, int y,
        std::array<std::array<bool, Game::WIDTH>, Game::HEIGHT>& visited);
};

#endif