#include "cactus.h"

#include "ncurses_model.h"
#include "frames.h"

#include <ncurses.h>

Cactus::Cactus(WINDOW* win, int x, int y)
    : NcursesModel(win,
                    {
                        Frames::Cactus::cactus,
                        Frames::Cactus::cactus2,
                        Frames::Cactus::cactus3,
                        Frames::Cactus::cactus4
                    },

                   x, y)
{

}
