#include "Cell.h"

void Cell::update_top(bool top) {
    this->top = top;
    this->update();
}
bool Cell::get_top() { return top; }
void Cell::update_bottom(bool bottom) {
    this->bottom = bottom;
    this->update();
}
bool Cell::get_bottom() { return bottom; }
void Cell::update_left(bool left) {
    this->left = left;
    this->update();
}
bool Cell::get_left() { return left; }
void Cell::update_right(bool right) {
    this->right = right;
    this->update();
}
bool Cell::get_right() { return right; }

void Cell::update() {
    wborder_set(this->w, this->left ? &Cell::OPEN : &Cell::VLINE,
                this->right ? &Cell::OPEN : &Cell::VLINE,
                this->top ? &Cell::OPEN : &Cell::HLINE,
                this->bottom ? &Cell::OPEN : &Cell::HLINE, &Cell::CORNER,
                &Cell::CORNER, &Cell::CORNER, &Cell::CORNER);

    if (this->fulfiled()) wattron(this->w, COLOR_PAIR(2) | A_BOLD);

    mvwprintw(this->w, CELL_HEIGHT / 2, CELL_WIDTH / 2, "%d", this->value);

    if (this->fulfiled()) wattroff(this->w, COLOR_PAIR(2) | A_BOLD);

    wrefresh(this->w);
}

cchar_t Cell::CORNER, Cell::VLINE, Cell::HLINE, Cell::OPEN;
void Cell::init_cchars() {
    setcchar(&Cell::VLINE, L"│", A_NORMAL, COLOR_PAIR(1), nullptr);
    setcchar(&Cell::CORNER, L"┼", A_NORMAL, COLOR_PAIR(1), nullptr);
    setcchar(&Cell::HLINE, L"─", A_NORMAL, COLOR_PAIR(1), nullptr);
    setcchar(&Cell::OPEN, L" ", A_NORMAL, COLOR_PAIR(1), nullptr);
}

bool Cell::fulfiled() { return left + right + top + bottom == this->value; }