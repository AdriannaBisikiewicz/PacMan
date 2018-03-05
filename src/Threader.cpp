#include <iostream>
#include <thread>
#include <ncurses.h>
#include <unistd.h>

using namespace std;
#define DELAY 60000

void make_ball(int y)
{
  int x = 0;
  int max_y = 0, max_x = 0;
  int next_x = 0;
  int direction = 1;

  getmaxyx(stdscr, max_y, max_x);

  while (1)
  {
    clear();
    mvprintw(y, x, "o");
    refresh();

    usleep(DELAY);

    next_x = x + direction;

    if (next_x >= max_x || next_x < 0)
    {
      direction *= -1;
    }
    else
    {
      x += direction;
    }
  }
}

int main(int argc, char *argv[])
{
  initscr();
  noecho();
  curs_set(FALSE);

  make_ball(0);

  endwin();
}