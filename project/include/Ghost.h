#include <ncurses.h>
class Ghost
{
    int coordinate_x;
    int coordinate_y;
  public :
    Ghost();
    Ghost(int x, int y);
    void moveFromSideToSide(WINDOW *w, int delay);
};
