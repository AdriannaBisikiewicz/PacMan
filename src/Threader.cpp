#include <iostream>
#include <thread>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "include/Ghost.h"

using namespace std;
#define RDELAY 1
Ghost ghost;

void make_ball(int y, WINDOW *w, int delay)
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
    mvwprintw(w, y, x, "o");
    prev_y = y;
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
// metoda, która w osobnym wątku odświeza nam nasze okno
void refresh_screen(WINDOW *w)
{
  while(1)
  {
    box(w, '|', '-');
    wrefresh(w);
    usleep(RDELAY);
  }
}

int main(int argc, char *argv[])
{
  WINDOW *window; // potrzebujemy go, aby móx zrobić obramowanie 
  int maxx, maxy;
  initscr();
  noecho();
  curs_set(FALSE);
  getmaxyx(stdscr, maxy, maxx);

  window = newwin(maxy, maxx, 0, 0);
  box(window,'|','-'); // metoda tworząca obramowanie
  mvwaddstr(window, 0, 0, "");
  wrefresh(window);

  thread t1(make_ball,5,window,10000);
  thread t2(make_ball,8,window,20000);
  thread t3(make_ball,11,window,30000);
  thread t4(make_ball,14,window,40000);
  thread t5(make_ball,17,window,50000);
  thread t6(make_ball,20,window,60000);
  thread t7(make_ball,23,window,70000);
  thread t8(make_ball,26,window,80000);
  thread t_r(refresh_screen,window);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  t7.join();
  t8.join();
  t_r.join();

  endwin();
}