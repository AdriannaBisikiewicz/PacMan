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
    char *map[height][width+1] ={"                              |                             ",
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
    for(int x=0;x<height;x++)
    {
        for(int y = 0;y<width;y++)
        {
            mvwprintw(w, y+1, x+1, map[x][y]);
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