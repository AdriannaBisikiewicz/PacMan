#include "MapProvider.h"
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

using namespace std;

MapProvider::MapProvider()
{
    width = 60;
    height = 30;
}

void MapProvider::ApplyMap(WINDOW *w)
{
    char map[height][width+1];
    ifstream stream;
    stream.open("map.txt");
    for(int y=0;y<height;y++){
        for(int x=0; x<width+1; x++){
            stream.get(map[y][x]);
        }
    }
    stream.close();
    wattron(w,COLOR_PAIR(6));
    box(w, '|', '-'); // metoda tworząca obramowanie
    wattroff(w,COLOR_PAIR(6));
    mvwaddstr(w, 0, 0, "");
    wrefresh(w);

    for(int x=0;x<width;x++)
    {
        for(int y = 0;y<height;y++)
        {
            if(map[y][x] == '|' || map[y][x] == '-' || map[y][x] == '#')
            {
                wattron(w,COLOR_PAIR(6));
                mvwaddch(w, y+1, x+1, map[y][x]);
                wattroff(w,COLOR_PAIR(6));
            }
            else
            {
                mvwaddch(w, y+1, x+1, map[y][x]);
            }
        }
    }
    wrefresh(w);
}

int MapProvider::GetHeight()
{
    return height;
}


int MapProvider::GetWidth()
{
    return width;
}