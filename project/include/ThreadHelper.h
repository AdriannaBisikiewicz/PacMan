#include <mutex>
#include <condition_variable>
class ThreadHelper
{
public:
  static void Lock();
  static void Unlock();
  static void Wait();
  static void Notify();

private:
  static std::mutex threadGuard;
  static std::condition_variable scoreCondition;
  ThreadHelper(){};
};