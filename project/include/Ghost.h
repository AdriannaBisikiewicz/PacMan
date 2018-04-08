#include <ncurses.h>
class Ghost
{
  int coordinate_x;
  int coordinate_y;
  int distance;
  int direction;
  bool isOn;
  void ChangeDirection();
  bool CantGo(WINDOW *w);

public:
  Ghost();
  Ghost(int x, int y);
  void Move(WINDOW *w, int delay, int colour);
  void StopGhost();
};
