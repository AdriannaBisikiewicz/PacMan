#include <ncurses.h>
class Player
{
  int coordinate_x;
  int coordinate_y;
  int distance;
  int direction;
  bool pacmanMouth;
  void ChangeDirection();
  bool CantGo(WINDOW *w);

public:
  Player();
  Player(int x, int y);
  void Move(WINDOW *w, int delay);
  void OpenOrCloseMouth(int delay);
};
