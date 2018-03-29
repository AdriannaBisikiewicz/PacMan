#include "Ghost.h"
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h> 
#include <iostream>

using namespace std;

void Ghost::ChangeDirection()
{
    direction = rand() % 4 + 1; 
}

bool Ghost::CantGo(WINDOW *w)
{
    bool result = true;
    switch(direction){
        case 1:
            result = (mvwinch(w, coordinate_y, coordinate_x-1) == '|' || mvwinch(w, coordinate_y, coordinate_x-1) == '-');
        break;
        case 2:
            result = (mvwinch(w, coordinate_y+1, coordinate_x) == '|' || mvwinch(w,  coordinate_y+1, coordinate_x) == '-');
        break;
        case 3:
            result = (mvwinch(w, coordinate_y, coordinate_x+1) == '|' || mvwinch(w, coordinate_y, coordinate_x+1) == '-');
        break;
        case 4:
            result = (mvwinch(w, coordinate_y-1, coordinate_x) == '|' || mvwinch(w,  coordinate_y-1, coordinate_x) == '-');
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
        mvwprintw(w, coordinate_y, x, "G");
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

void Ghost::Move(WINDOW *w, int delay)
{
    int prev_x = coordinate_x, prev_y = coordinate_y;
    while (1)
    {
        while(CantGo(w))
        {
            ChangeDirection();
        }
        mvwprintw(w, prev_y, prev_x, " "); // nieładnie, ale zamiast czyścić cały ekran w poprzednie miejsce duszka wstawiamy pusty znak, przez co się nie krzaczy
        mvwprintw(w, coordinate_y, coordinate_x, "G");
        prev_y = coordinate_y;
        prev_x = coordinate_x;
        usleep(delay);
        switch(direction){
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
