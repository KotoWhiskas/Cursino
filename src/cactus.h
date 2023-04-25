#ifndef CACTUS_H
#define CACTUS_H

#include "ncurses_model.h"

#include <ncurses.h>

class Cactus : public NcursesModel
{
public:
    Cactus(WINDOW* win = stdscr, int x = 20, int y = 20);

};


#endif
