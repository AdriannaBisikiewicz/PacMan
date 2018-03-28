#include <ncurses.h>
class Ghost
{
    int coordinate_x;
    int coordinate_y;
    int distance;
    int direction;
    void ChangeDirection();
    bool CantGo(WINDOW *w);
  public :
    Ghost();
    Ghost(int x, int y);
    void moveFromSideToSide(WINDOW *w, int delay);
    void Move(WINDOW *w, int delay);
};
