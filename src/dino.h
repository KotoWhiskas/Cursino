#ifndef DINO_H
#define DINO_H


#include "ncurses_model.h"

#include <ncurses.h>
#include <vector>
#include <stdexcept>


class Dino : public NcursesModel
{
public:
    Dino(WINDOW* win = stdscr);
};

#endif
