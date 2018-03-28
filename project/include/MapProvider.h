#include <ncurses.h>
class MapProvider{
    int width, height;
    public:
        MapProvider();
        void ApplyMap(WINDOW *w);
        int GetHeight();
        int GetWidth();
};