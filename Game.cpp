#include "Game.h"

#include <stdlib.h>

#include <vector>

Game::Game(std::array<std::array<int, Game::WIDTH>, Game::HEIGHT> vals) {
    // int vals[][Game::WIDTH] = {
    //     {1, 2, 2, 1}, {2, 3, 3, 2}, {2, 3, 3, 2}, {1, 1, 1, 1}};
    for (int j = 0; j < Game::HEIGHT; j++) {
        for (int i = 0; i < Game::WIDTH; i++) {
            this->cellss[j][i] = Cell(j, i, vals[j][i]);
        }
    }
    update_cursor();
}

void Game::move_cursor_left() {
    if (vx != 0) vx -= 1;
    if (hx != 0) hx -= 1;
    this->update_cursor();
}

void Game::move_cursor_right() {
    if (vx != Game::WIDTH - 2) vx += 1;
    if (hx != Game::WIDTH - 1) hx += 1;
    this->update_cursor();
}

void Game::move_cursor_up() {
    if (is_vertical) {
        if (vy == 0) return;
        hy = vy - 1;
        is_vertical = false;
    } else {
        vy = hy;
        is_vertical = true;
    }
    this->update_cursor();
}

void Game::move_cursor_down() {
    if (is_vertical) {
        if (vy == Game::HEIGHT - 1) return;
        hy = vy;
        is_vertical = false;
    } else {
        vy = hy + 1;
        is_vertical = true;
    }
    this->update_cursor();
}

std::pair<int, int> Game::get_pos() {
    if (is_vertical) {
        return std::make_pair(PADDING + (CELL_WIDTH - 1) * (this->vx + 1),
                              PADDING + CELL_HEIGHT / 2 + 2 * this->vy);
    } else {
        return std::make_pair(
            PADDING + (CELL_WIDTH - 1) * (this->hx + 1) - CELL_WIDTH / 2,
            PADDING + CELL_HEIGHT / 2 + 2 * this->hy + 1);
    }
}

void Game::update_cursor() {
    auto pos = get_pos();
    move(pos.second, pos.first);
    refresh();
}

void Game::toggle_door() {
    bool is_open;
    if (is_vertical) {
        is_open = v_doorss[vy][vx];
        is_open = !is_open;
        v_doorss[vy][vx] = is_open;
        this->cellss[vy][vx].update_right(is_open);
        this->cellss[vy][vx + 1].update_left(is_open);
    } else {
        is_open = h_doorss[hy][hx];
        is_open = !is_open;
        h_doorss[hy][hx] = is_open;
        this->cellss[hy][hx].update_bottom(is_open);
        this->cellss[hy + 1][hx].update_top(is_open);
    }
    update_cursor();
}

void Game::print() {
    for (auto cells : this->cellss) {
        for (auto cell : cells) {
            cell.update();
        }
    }
}

bool Game::fulfilled() {
    for (auto cells : this->cellss) {
        for (auto cell : cells) {
            if (!cell.fulfiled()) return false;
        }
    }
    std::array<std::array<bool, Game::WIDTH>, Game::HEIGHT> visited = {};
    return Game::fulfilledHelp(0, 0, visited) == Game::WIDTH * Game::HEIGHT;
}

int Game::fulfilledHelp(
    int x, int y,
    std::array<std::array<bool, Game::WIDTH>, Game::HEIGHT>& visited) {
    if (visited[y][x]) return 0;
    visited[y][x] = true;
    int count = 1;
    if (this->cellss[y][x].get_top())
        count += this->fulfilledHelp(x, y - 1, visited);
    if (this->cellss[y][x].get_bottom())
        count += this->fulfilledHelp(x, y + 1, visited);
    if (this->cellss[y][x].get_left())
        count += this->fulfilledHelp(x - 1, y, visited);
    if (this->cellss[y][x].get_right())
        count += this->fulfilledHelp(x + 1, y, visited);
    return count;
}

Game* Game::generate(unsigned int seed) {
    srand(seed);
    typedef std::pair<int, int> Coordinate;
    std::array<std::array<int, Game::WIDTH>, Game::HEIGHT> values = {};
    std::vector<std::pair<Coordinate, Coordinate>> laters;
    laters.reserve(Game::HEIGHT * Game::WIDTH);

    laters.push_back(
        std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0)));
    while (laters.size() != 0) {
        std::iter_swap(laters.begin() + rand() % laters.size(),
                       laters.end() - 1);
        auto pair = laters.back();
        laters.pop_back();
        int x = pair.second.first;
        int y = pair.second.second;
        if (x == -1 || y == -1 || x == Game::WIDTH || y == Game::HEIGHT ||
            values[y][x] != 0)
            continue;
        values[pair.first.second][pair.first.first] += 1;
        values[pair.second.second][pair.second.first] += 1;

        for (int dx = -1; dx <= 1; dx += 2) {
            laters.push_back(
                std::make_pair(pair.second, std::make_pair(x + dx, y)));
        }
        for (int dy = -1; dy <= 1; dy += 2) {
            laters.push_back(
                std::make_pair(pair.second, std::make_pair(x, y + dy)));
        }
    }
    values[0][0] -= 2;
    return new Game(values);
}