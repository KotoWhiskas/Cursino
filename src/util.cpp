#include "util.h"

#include <random>
#include <iostream>
#include <ncurses.h>
#include <vector>
#include <chrono>
#include <thread>

std::mt19937 mt{std::random_device{}()};

int getRandom(int start, int end)
{
    return std::uniform_int_distribution<>{start, end}(mt);
}

void sleep(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

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

void drawGameOver()
{
    mvwprintw(stdscr, getmaxy(stdscr) / 2, getmaxx(stdscr) / 2, "GAME OVER");

    refresh();
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
                    ;
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

