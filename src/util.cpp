#include "util.h"

#include <iostream>
#include <ncurses.h>
#include <vector>

void clearMatrix(WINDOW* screen, int x, int y, const std::vector<std::string>& matrix)
{
    int rowcenterItem{static_cast<int>(matrix.at(0).size()  / 2)};
    int colcenterItem{static_cast<int>(matrix.size()        / 2)};


    for (int column{}; column < matrix.size(); ++column)
    {
        for (int row{}; row < matrix.at(0).size(); ++row)
        {
            mvwaddch(screen,
                     y + column - colcenterItem,
                     x + row    - rowcenterItem,
                     ' ');
        }
    }

    wrefresh(stdscr);


}

void printMatrix(WINDOW* screen, int x, int y, const std::vector<std::string>& matrix, bool* panic_status, bool panic)
{
    int rowcenterItem{static_cast<int>(matrix.at(0).size()  / 2)};
    int colcenterItem{static_cast<int>(matrix.size()        / 2)};


    for (int column{}; column < matrix.size(); ++column)
    {
        for (int row{}; row < matrix.at(0).size(); ++row)
        {
            if (panic)
            {

                if (matrix[column][row] != ' ' &&
                    mvwinch(screen,
                            y + column - colcenterItem,
                            x + row    - rowcenterItem) != ' '

                    && panic_status)
                {
                    *panic_status = true;
                }
            }

            mvwaddch(screen,
                     y + column - colcenterItem,
                     x + row    - rowcenterItem,
                     matrix[column][row]);

        }
    }

    wrefresh(stdscr);


}

