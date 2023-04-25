#include "dino.h"

#include "frames.h"

#include <ncurses.h>

Dino::Dino(WINDOW* win)
: NcursesModel{win, {Frames::Dino::dino1,
                     Frames::Dino::dino2,
                     Frames::Dino::dino3}, 20, 20}
{

}
