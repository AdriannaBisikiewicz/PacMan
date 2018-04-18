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

void Player::ChangeDirection(WINDOW *w,int key)
{
    if(CanGo(w, key))
    {
        direction = key;
        n_direction = direction;
    }
    else
    {
        n_direction = key;
    }
}

bool Player::CanGo(WINDOW *w, int dir)
{
    int color;
    switch (dir)
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
    return color != COLOR_PAIR(6);
}

Player::Player() {}

Player::Player(int x, int y)
{
    coordinate_x = x;
    coordinate_y = y;
    distance = 0;
    direction = 4; // 1-left, 3-right, 4-up, 2-down
    n_direction = direction;
    pacmanMouth = true;
    isOn = true;
    score = 0;
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

void Player::WritePoints(WINDOW *w)
{
    while (isOn)
    {
        ThreadHelper::Wait();
        score++;
        mvwprintw(w, 10, 11, std::to_string(score).c_str());
    }
}

void Player::Move(WINDOW *w, int delay)
{
    int prev_x = coordinate_x, prev_y = coordinate_y;
    while (isOn)
    {
        ThreadHelper::Lock();
        if(direction != n_direction && CanGo(w,n_direction))
        {
            direction = n_direction;
        }
        if (CanGo(w, direction))
        {
            distance = 1;
        }
        else distance = 0;

        switch (direction)
        {

        case 1:
            coordinate_x -= distance;
            break;
        case 2:
            coordinate_y += distance;
            break;
        case 3:
            coordinate_x += distance;
            break;
        case 4:
            coordinate_y -= distance;
            break;
        }

        mvwprintw(w, prev_y, prev_x, " ");
        if (mvwinch(w, coordinate_y, coordinate_x) == '*')
        {
            ThreadHelper::Notify();
        }
        wattron(w, COLOR_PAIR(5));
        if (pacmanMouth)
        {
            mvwaddch(w, coordinate_y, coordinate_x, 'O');
        }
        else
        {
            mvwaddch(w, coordinate_y, coordinate_x, 'C');
        }
        wattroff(w, COLOR_PAIR(5));
        prev_y = coordinate_y;
        prev_x = coordinate_x;
        ThreadHelper::Unlock();
        usleep(delay);
    }
}
