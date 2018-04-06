#include "Ghost.h"
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <mutex>
#include <iostream>
#include "ThreadHelper.h"

using namespace std;

void Ghost::ChangeDirection()
{
    direction = rand() % 4 + 1;
}

bool Ghost::CantGo(WINDOW *w)
{
    bool result = true;
    switch (direction)
    {
    case 1:
        result = (mvwinch(w, coordinate_y, coordinate_x - 1) == '|' || mvwinch(w, coordinate_y, coordinate_x - 1) == '-');
        break;
    case 2:
        result = (mvwinch(w, coordinate_y + 1, coordinate_x) == '|' || mvwinch(w, coordinate_y + 1, coordinate_x) == '-');
        break;
    case 3:
        result = (mvwinch(w, coordinate_y, coordinate_x + 1) == '|' || mvwinch(w, coordinate_y, coordinate_x + 1) == '-');
        break;
    case 4:
        result = (mvwinch(w, coordinate_y - 1, coordinate_x) == '|' || mvwinch(w, coordinate_y - 1, coordinate_x) == '-');
        break;
    }
    return result;
}

Ghost::Ghost() {}

Ghost::Ghost(int x, int y)
{
    coordinate_x = x;
    coordinate_y = y;
    distance = 1;
    direction = 2; // 1-left, 3-right, 4-up, 2-down
}

void Ghost::Move(WINDOW *w, int delay)
{
    int prev_x = coordinate_x, prev_y = coordinate_y;
    while (1)
    {
        ThreadHelper::Lock();
        while (CantGo(w))
        {
            ChangeDirection();
        }
        mvwprintw(w, prev_y, prev_x, " "); // nieładnie, ale zamiast czyścić cały ekran w poprzednie miejsce duszka wstawiamy pusty znak, przez co się nie krzaczy
        mvwprintw(w, coordinate_y, coordinate_x, "G");
        prev_y = coordinate_y;
        prev_x = coordinate_x;
        ThreadHelper::Unlock();
        usleep(delay);
        switch (direction)
        {
        case 1:
            coordinate_x--;
            break;
        case 2:
            coordinate_y++;
            break;
        case 3:
            coordinate_x++;
            break;
        case 4:
            coordinate_y--;
            break;
        }
    }
}
