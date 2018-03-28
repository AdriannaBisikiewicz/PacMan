#include <iostream>
#include <thread>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "Ghost.h"
#include "MapProvider.h"

using namespace std;
#define RDELAY 1

// metoda, która w osobnym wątku odświeza nam nasze okno
void refresh_screen(WINDOW *w)
{
  while (1)
  {
    box(w, '|', '-');
    wrefresh(w);
    usleep(RDELAY);
  }
}

int main(int argc, char *argv[])
{

  WINDOW *window; // potrzebujemy go, aby móx zrobić obramowanie
  MapProvider *mapProvider = new MapProvider();
  int maxx, maxy;
  initscr();
  noecho();
  curs_set(FALSE);

  window = newwin(mapProvider->GetHeight()+2, mapProvider->GetWidth()+2, 0, 0);
  box(window, '|', '-'); // metoda tworząca obramowanie
  mvwaddstr(window, 0, 0, "");
  mapProvider->ApplyMap(window);
  wrefresh(window);
  Ghost ghosts[4] = {Ghost(0, 5), Ghost(0, 8), Ghost(0, 14), Ghost(0, 23)};

  // thread t1(&Ghost::moveFromSideToSide, &ghosts[0], window, 10000);
  // thread t2(&Ghost::moveFromSideToSide, &ghosts[1], window, 20000);
  // thread t3(&Ghost::moveFromSideToSide, &ghosts[2], window, 30000);
  // thread t4(&Ghost::moveFromSideToSide, &ghosts[3], window, 40000);
  // przerysowywanie ekranu
  thread t_r(refresh_screen, window);

  // t1.join();
  // t2.join();
  // t3.join();
  // t4.join();

  t_r.join();

  endwin();
}