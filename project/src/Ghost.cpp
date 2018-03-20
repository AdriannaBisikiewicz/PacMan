#include "Ghost.h"
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#include <iostream>

using namespace std;

Ghost::Ghost() {}

Ghost::Ghost(int x, int y)
{
    coordinate_x = x;
    coordinate_y = y;
}
void Ghost::moveFromSideToSide(WINDOW *w, int delay)
{
    int x = 1; // zeby kulka nie wchodziła w ramę
    int max_y = 0, max_x = 0;
    int next_x = 0;
    int direction = 1;
    int prev_x = 0, prev_y = 0;

    getmaxyx(w, max_y, max_x);
    max_x--; // zeby kulka nie wchodziła w ramę

    while (1)
    {
        mvwprintw(w, prev_y, prev_x, " "); // nieładnie, ale zamiast czyścić cały ekran w poprzednie miejsce duszka wstawiamy pusty znak, przez co się nie krzaczy
        mvwprintw(w, coordinate_y, x, "o");
        prev_y = coordinate_y;
        prev_x = x;
        usleep(delay);

        next_x = x + direction;
        if (next_x >= max_x || next_x < 1) // zeby kulka nie wchodziła w ramę
        {
            direction *= -1;
        }
        else
        {
            x += direction;
        }
    }
}
