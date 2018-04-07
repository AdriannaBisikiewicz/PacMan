#include <iostream>
#include <thread>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "ThreadHelper.h"
#include "Ghost.h"
#include "Player.h"
#include "MapProvider.h"
#include "InformationProvider.h"
#include <time.h>
#include <mutex>

using namespace std;
#define RDELAY 10000
Player player;
Ghost *ghosts;

// metoda, która w osobnym wątku odświeza nam nasze okno
void refresh_screen(WINDOW *mw, WINDOW *iw)
{
  while (1)
  {
    ThreadHelper::Lock();
    wrefresh(mw);
    wrefresh(iw);
    ThreadHelper::Unlock();
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
  WINDOW *main_window;
  WINDOW *information_window;
  MapProvider *mapProvider = new MapProvider();
  InformationProvider *informationProvider = new InformationProvider();
  initscr();
  noecho();
  curs_set(FALSE);
  refresh(); // Need this to let other windows be drawn

  main_window = newwin(mapProvider->GetHeight() + 2, mapProvider->GetWidth() + 2, 0, 0);
  information_window = newwin(informationProvider->GetHeight() + 2,informationProvider->GetWidth() + 2, 0, mapProvider->GetWidth()+1);

  mapProvider->ApplyMap(main_window);
  informationProvider->ApplyInformation(information_window);  refresh();

  ghosts = new Ghost[4];
  ghosts[0] = Ghost(17, 12);
  ghosts[1] = Ghost(17, 14);
  ghosts[2] = Ghost(44, 12);
  ghosts[3] = Ghost(44, 14);

  player = Player(30, 7);

  thread t1(&Ghost::Move, &ghosts[0], main_window, 60000);
  thread t2(&Ghost::Move, &ghosts[1], main_window, 60000);
  thread t3(&Ghost::Move, &ghosts[2], main_window, 60000);
  thread t4(&Ghost::Move, &ghosts[3], main_window, 60000);
  //Player threads
  thread t5(&Player::Move, &player, main_window, 60000);
  thread t6(&Player::OpenOrCloseMouth, &player, 600000);
  // przerysowywanie ekranu
  thread t_r(refresh_screen, main_window, information_window);
  // keyboard
  thread t_k(keyboard_input, main_window);

  //mvwprintw(information_window, 10, 13, "1"); Miejsce, w którym jest liczba jedności naszego score

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