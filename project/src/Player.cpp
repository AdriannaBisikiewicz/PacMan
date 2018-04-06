#include "Player.h"
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <mutex>
#include <time.h> 
#include <iostream>

using namespace std;
std::mutex playerGuard;


void Player::ChangeDirection()
{
    direction = rand() % 4 + 1; 
}

bool Player::CantGo(WINDOW *w)
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

Player::Player() {}

Player::Player(int x, int y)
{
    coordinate_x = x;
    coordinate_y = y;
    distance = 1;
    direction = 2; // 1-left, 3-right, 4-up, 2-down 
}

void Player::Move(WINDOW *w, int delay)
{
    int prev_x = coordinate_x, prev_y = coordinate_y;
    while (1)
    {
        playerGuard.lock();
        while(CantGo(w))
        {
            ChangeDirection();
        }
        mvwprintw(w, prev_y, prev_x, " "); // nieładnie, ale zamiast czyścić cały ekran w poprzednie miejsce duszka wstawiamy pusty znak, przez co się nie krzaczy
        mvwprintw(w, coordinate_y, coordinate_x, "O");
        prev_y = coordinate_y;
        prev_x = coordinate_x;
        playerGuard.unlock();
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
