#include "InformationProvider.h"
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

using namespace std;

InformationProvider::InformationProvider()
{
    width = 14;
    height = 30;
}

void InformationProvider::ApplyInformation(WINDOW *w)
{
    char information[height][width+1];
    ifstream stream;
    stream.open("information.txt");
    for(int y=0;y<height;y++){
        for(int x=0; x<width+1; x++){
            stream.get(information[y][x]);
        }
    }
    stream.close();

    box(w, '|', '-'); // metoda tworząca obramowanie
    mvwaddstr(w, 0, 0, "");
    wrefresh(w);

    for(int x=0;x<width;x++)
    {
        for(int y = 0;y<height;y++)
        {
            mvwaddch(w, y+1, x+1, information[y][x]);
        }
    }
    wrefresh(w);
}

int InformationProvider::GetHeight()
{
    return height;
}


int InformationProvider::GetWidth()
{
    return width;
}