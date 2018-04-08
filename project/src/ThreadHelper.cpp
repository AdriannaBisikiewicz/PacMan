#include "ThreadHelper.h"
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
std::mutex ThreadHelper::threadGuard;
std::condition_variable ThreadHelper::scoreCondition;
bool foundPoint = false;

void ThreadHelper::Lock()
{
    threadGuard.lock();
}

void ThreadHelper::Unlock()
{
    threadGuard.unlock();
}

void ThreadHelper::Wait()
{
    std::unique_lock<std::mutex> scoreLock(threadGuard);
    foundPoint = false;
    scoreCondition.wait(scoreLock, []{ return foundPoint; });
}

void ThreadHelper::Notify()
{
    foundPoint = true;
    scoreCondition.notify_one();
}