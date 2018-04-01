#include "MapProvider.h"
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

MapProvider::MapProvider()
{
    width = 60;
    height = 30;
}

void MapProvider::ApplyMap(WINDOW *w)
{
    char map[height][width+1] ={ "                              |                             ",
                                 "                              |                             ",
                                 "        ----                  |               ----          ",
                                 "        |  |                  |               |  |          ",
                                 "        ----          -----------------       ----          ",
                                 "                                                            ",
                                 "                                                            ",
                                 "-------             ---------------------            -------",
                                 "                                                            ",
                                 "                                                            ",
                                 "       |            --------     --------           |       ",
                                 "       |            |                   |           |       ",
                                 "       |            |                   |           |       ",
                                 "       |            |                   |           |       ",
                                 "       |            ---------------------           |       ",
                                 "       |                                            |       ",
                                 "       |            ---------------------           |       ",
                                 "                              |                             ",
                                 "                              |                             ",
                                 "                              |                             ",
                                 "                                                            ",
                                 "     ------          ----           ----         ------     ",
                                 "       |                                            |       ",
                                 "       |                                            |       ",
                                 "                                                            ",
                                 "-----       |       ---------------------      |       -----",
                                 "            |                 |                |            ",
                                 "            |                 |                |            ",
                                 "      ----------              |             ----------      ",
                                 "                                                            "};
    for(int x=0;x<width;x++)
    {
        for(int y = 0;y<height;y++)
        {
            mvwaddch(w, y+1, x+1, map[y][x]);
        }
    }
}

int MapProvider::GetHeight()
{
    return height;
}


int MapProvider::GetWidth()
{
    return width;
}