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
    int color;
    switch (direction)
    {
    case 1:
        color = (mvwinch(w, coordinate_y, coordinate_x - 1) & A_COLOR);
        break;
    case 2:
        color = (mvwinch(w, coordinate_y + 1, coordinate_x) & A_COLOR);
        break;
    case 3:
        color = (mvwinch(w, coordinate_y, coordinate_x + 1) & A_COLOR);
        break;
    case 4:
        color = (mvwinch(w, coordinate_y - 1, coordinate_x) & A_COLOR);
        break;
    }
    return color == COLOR_PAIR(6);
}

Ghost::Ghost() {}

Ghost::Ghost(int x, int y)
{
    coordinate_x = x;
    coordinate_y = y;
    distance = 1;
    direction = 2; // 1-left, 3-right, 4-up, 2-down
    isOn = true;
}

void Ghost::StopGhost()
{
    isOn = false;
}

void Ghost::Move(WINDOW *w, int delay, int colour)
{
    bool wasPoint = false;
    int prev_x = coordinate_x, prev_y = coordinate_y;
    while (isOn)
    {
        ThreadHelper::Lock();
        if ((mvwinch(w, coordinate_y, coordinate_x) & A_COLOR) == COLOR_PAIR(5))
        {
            ThreadHelper::KillPacman();
        }

        while (CantGo(w))
        {
            ChangeDirection();
        }
        if (wasPoint)
        {
            mvwprintw(w, prev_y, prev_x, "*");
        }
        else
        {
            mvwprintw(w, prev_y, prev_x, " "); // nieładnie, ale zamiast czyścić cały ekran w poprzednie miejsce duszka wstawiamy pusty znak, przez co się nie krzaczy
        }
        wasPoint = (mvwinch(w, coordinate_y, coordinate_x) == '*');
        wattron(w, COLOR_PAIR(colour));
        mvwprintw(w, coordinate_y, coordinate_x, "G");
        wattroff(w, COLOR_PAIR(colour));

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
