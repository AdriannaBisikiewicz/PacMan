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
#define RDELAY 100000
Player player;
Ghost *ghosts;
WINDOW *main_window;
WINDOW *information_window;

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

void gameOver()
{
  ThreadHelper::WaitForPacmanDeath();
  player.StopPlayer();
  for (int i = 0; i < 4; i++)
  {
    ghosts[i].StopGhost();
  }

  usleep(1000000);
  endwin();
  exit(0);
}

void keyboard_input(WINDOW *w)
{
  cbreak(); // each key the user hits is returned immediately by getch()

  int ch;
  nodelay(stdscr, TRUE);
  for (;;)
  {
    if ((ch = getch()) == ERR)
    {
    }
    // user pushes or holds a key
    else
    {
      // h - EXIT
      if (ch == 104)
      {
        ThreadHelper::KillPacman();
      }
      // Left
      if (ch == 97)
      {
        player.ChangeDirection(main_window,1);
      }
      // Up
      if (ch == 119)
      {
        player.ChangeDirection(main_window,4);
      }
      // Right
      if (ch == 100)
      {
        player.ChangeDirection(main_window,3);
      }
      // Down
      if (ch == 115)
      {
        player.ChangeDirection(main_window,2);
      }
    }
  }
}

void initialize_ncurses()
{
  srand(time(NULL));
  initscr();
  noecho();
  curs_set(FALSE);
  start_color();
  refresh(); // Need this to let other windows be drawn
}

void initialize_colors()
{
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  init_pair(4, COLOR_CYAN, COLOR_BLACK);
  init_pair(5, COLOR_YELLOW, COLOR_BLACK);
  init_pair(6, COLOR_BLUE, COLOR_BLACK);
}

void initialize_windows()
{
  MapProvider *mapProvider = new MapProvider();
  InformationProvider *informationProvider = new InformationProvider();

  main_window = newwin(mapProvider->GetHeight() + 2, mapProvider->GetWidth() + 2, 0, 0);
  information_window = newwin(informationProvider->GetHeight() + 2, informationProvider->GetWidth() + 2, 0, mapProvider->GetWidth() + 2);

  mapProvider->ApplyMap(main_window);
  informationProvider->ApplyInformation(information_window);
}

void create_threads()
{
  thread t1(&Ghost::Move, &ghosts[0], main_window, 60000, 1);
  thread t2(&Ghost::Move, &ghosts[1], main_window, 60000, 2);
  thread t3(&Ghost::Move, &ghosts[2], main_window, 60000, 3);
  thread t4(&Ghost::Move, &ghosts[3], main_window, 60000, 4);
  //Player threads
  thread t5(&Player::Move, &player, main_window, 60000);
  thread t6(&Player::OpenOrCloseMouth, &player, 600000);
  thread tp(&Player::WritePoints, &player, information_window);
  // przerysowywanie ekranu
  thread t_r(refresh_screen, main_window, information_window);
  // keyboard
  thread t_k(keyboard_input, main_window);
  // game over
  thread t_go(gameOver);

  //mvwprintw(information_window, 10, 13, "1"); Miejsce, w którym jest liczba jedności naszego score

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  tp.join();
  t_r.join();
  t_k.join();
  t_go.join();
}

void initialize_objects()
{
  ghosts = new Ghost[4];
  ghosts[0] = Ghost(17, 12);
  ghosts[1] = Ghost(17, 14);
  ghosts[2] = Ghost(44, 12);
  ghosts[3] = Ghost(44, 14);

  player = Player(30, 7);
}

int main(int argc, char *argv[])
{
  initialize_ncurses();

  initialize_colors();

  initialize_windows();

  initialize_objects();

  create_threads();

  endwin();
}