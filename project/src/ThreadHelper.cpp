#include "ThreadHelper.h"
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
std::mutex ThreadHelper::threadGuard;

void ThreadHelper::Lock()
{
    threadGuard.lock();
}

void ThreadHelper::Unlock()
{
    threadGuard.unlock();
}

