#include <iostream>
#include <thread>
#include <ncurses.h>

using namespace std;

void hello_world()
{
  printw("Hello from thread!\n");
  refresh();
  getch();
}

int main()
{
  initscr();
  thread t(hello_world);
  t.join();
  endwin();
  return 0;
}