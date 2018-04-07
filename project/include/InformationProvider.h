#include <ncurses.h>
class InformationProvider{
    int width, height;
    public:
        InformationProvider();
        void ApplyInformation(WINDOW *w);
        int GetHeight();
        int GetWidth();
};