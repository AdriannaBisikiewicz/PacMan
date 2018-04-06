#include <mutex>

class ThreadHelper
{
public:
  static void Lock();
  static void Unlock();

private:
  static std::mutex threadGuard;
  ThreadHelper(){};
};