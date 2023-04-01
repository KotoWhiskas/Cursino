#include "dino.h"

#include "frames.h"

#include <ncurses.h>

Dino::Dino(WINDOW* win, int x, int y)
: NcursesModel{win, {Frames::Dino::dino1,
                     Frames::Dino::dino2,
                     Frames::Dino::dino3}, x, y}
{

}
