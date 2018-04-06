#include <iostream>
#include <thread>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "Ghost.h"
#include "Player.h"
#include "MapProvider.h"
#include <time.h>
#include <mutex>

using namespace std;
#define RDELAY 10000
std::mutex refreshGuard;
Player player;
Ghost *ghosts;

// metoda, która w osobnym wątku odświeza nam nasze okno
void refresh_screen(WINDOW *w)
{
  while (1)
  {
    refreshGuard.lock();
    box(w, '|', '-');
    wrefresh(w);
    refreshGuard.unlock();
    usleep(RDELAY);
  }
}

void keyboard_input(WINDOW *w)
{
  cbreak(); // each key the user hits is returned immediately by getch()

  int ch;
  nodelay(stdscr, TRUE);
  for (;;)
  {
    if ((ch = getch()) == ERR){}
    // uzytkownik wciska klawisz
    else
    {
      // ESC
      if (ch == 27)
      {
        player.StopPlayer();
        for (int i=0; i<4; i++){
          ghosts[i].StopGhost();
        }
      }
    }
  }
}

int main(int argc, char *argv[])
{
  srand(time(NULL));
  WINDOW *window; // potrzebujemy go, aby móx zrobić obramowanie
  MapProvider *mapProvider = new MapProvider();
  int maxx, maxy;
  initscr();
  noecho();
  curs_set(FALSE);

  window = newwin(mapProvider->GetHeight() + 2, mapProvider->GetWidth() + 2, 0, 0);
  box(window, '|', '-'); // metoda tworząca obramowanie
  mvwaddstr(window, 0, 0, "");
  mapProvider->ApplyMap(window);
  wrefresh(window);
  ghosts = new Ghost[4];
  ghosts[0] = Ghost(17, 12);
  ghosts[1] = Ghost(17, 14);
  ghosts[2] = Ghost(44, 12);
  ghosts[3] = Ghost(44, 14);

  player = Player(30, 7);

  thread t1(&Ghost::Move, &ghosts[0], window, 60000);
  thread t2(&Ghost::Move, &ghosts[1], window, 60000);
  thread t3(&Ghost::Move, &ghosts[2], window, 60000);
  thread t4(&Ghost::Move, &ghosts[3], window, 60000);

  thread t5(&Player::Move, &player, window, 60000);
  thread t6(&Player::OpenOrCloseMouth, &player, 600000);
  // przerysowywanie ekranu
  thread t_r(refresh_screen, window);
  // keyboard
  thread t_k(keyboard_input, window);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  t_r.join();
  t_k.join();

  endwin();
}