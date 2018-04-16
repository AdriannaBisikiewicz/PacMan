#include <ncurses.h>
class Player
{
  int coordinate_x;
  int coordinate_y;
  int distance;
  int direction;
  bool pacmanMouth;
  bool isOn;
  bool CanGo(WINDOW *w);
  int score;

public:
  Player();
  Player(int x, int y);
  void Move(WINDOW *w, int delay);
  void OpenOrCloseMouth(int delay);
  void StopPlayer();
  void WritePoints(WINDOW *iw);
  void ChangeDirection(int);
};
