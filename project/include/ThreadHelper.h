#include <mutex>
#include <condition_variable>
class ThreadHelper
{
public:
  static void Lock();
  static void Unlock();
  static void Wait();
  static void Notify();
  static void WaitForPacmanDeath();
  static void KillPacman();

private:
  static std::mutex threadGuard;
  static std::condition_variable scoreCondition;
  static std::condition_variable deathCondition;

  ThreadHelper(){};
};