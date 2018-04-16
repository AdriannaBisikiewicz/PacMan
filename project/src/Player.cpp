#include "Player.h"
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <mutex>
#include <condition_variable>
#include <time.h>
#include <iostream>
#include "ThreadHelper.h"

using namespace std;

void Player::ChangeDirection()
{
    direction = rand() % 4 + 1;
}

bool Player::CantGo(WINDOW *w)
{
    int color;
    // switch (direction)
    // {
    // case 1:
    //     color = (mvwinch(w, coordinate_y, coordinate_x - 1) & A_COLOR);
    //     break;
    // case 2:
    //     color = (mvwinch(w, coordinate_y + 1, coordinate_x) & A_COLOR);
    //     break;
    // case 3:
    //     color = (mvwinch(w, coordinate_y, coordinate_x + 1) & A_COLOR);
    //     break;
    // case 4:
    //     color = (mvwinch(w, coordinate_y - 1, coordinate_x) & A_COLOR);
    //     break;
    // }
       color = (mvwinch(w, coordinate_y - 1, coordinate_x) & A_COLOR);
    return color == COLOR_PAIR(6);
}

Player::Player() {}

Player::Player(int x, int y)
{
    coordinate_x = x;
    coordinate_y = y;
    distance = 1;
    direction = 4; // 1-left, 3-right, 4-up, 2-down
    pacmanMouth = true;
    isOn = true;
    score = 0;
}

void Player::MoveByUser(int key)
{
    //direction = 1;
}
void Player::OpenOrCloseMouth(int delay)
{
    while (isOn)
    {
        usleep(delay);
        pacmanMouth = !pacmanMouth;
    }
}

void Player::StopPlayer()
{
    isOn = false;
}

void Player::WritePoints(WINDOW *iw)
{
    while (isOn)
    {
        ThreadHelper::Wait();
        score++;
        mvwprintw(iw, 10, 11, std::to_string(score).c_str());
    }
}

void Player::Move(WINDOW *w, int delay)
{
    int prev_x = coordinate_x, prev_y = coordinate_y;
    while (isOn)
    {
        if (!CantGo(w))
        {
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
        ThreadHelper::Lock();
        mvwprintw(w, prev_y, prev_x, " ");
        if (mvwinch(w, coordinate_y, coordinate_x) == '*')
        {
            ThreadHelper::Notify();
        }
        wattron(w, COLOR_PAIR(5));
        if (pacmanMouth)
        {
            mvwprintw(w, coordinate_y, coordinate_x, "O");
        }
        else
        {
            mvwprintw(w, coordinate_y, coordinate_x, "C");
        }
        wattroff(w, COLOR_PAIR(5));
        prev_y = coordinate_y;
        prev_x = coordinate_x;
        ThreadHelper::Unlock();
        usleep(delay);
    }
}
