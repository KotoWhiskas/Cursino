#include "dino.h"
#include "cactus.h"
#include "util.h"

#include <curses.h>
#include <memory>
#include <ncurses.h>
#include <string>
#include <array>
#include <cstddef>
#include <fstream>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <random>

namespace Random
{
    std::mt19937 mt{std::random_device{}()};
    std::uniform_int_distribution randomCactus{0, 3};
    std::uniform_int_distribution randomRange{-50, 20};

    int cactus()
    {
        return randomCactus(mt);
    }

    int range()
    {
        return randomRange(mt);
    }


}


void print(std::vector<std::string> vec)
{
    for (auto i : vec)
    {
        std::cout << i << '\n';
    }

}

void printScore(int score)
{
    std::string sscore{std::to_string(score)};
    int x{10};
    for (char i : sscore)
    {
        mvwaddch(stdscr, 1, x, i);
        x += 1;
    }

}

void printGameOver()
{
    std::string text{"Game over"};

    int midx{getmaxx(stdscr) / 2};
    int midy{getmaxy(stdscr) / 2};

    for (int i{}; i < text.length(); ++i)
    {
        mvwaddch(stdscr, midy, midx + i, text[i]);
    }
}


int main()
{
    int score{};

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, true);


    Dino dino{stdscr, 10, 20};
    Cactus cactus{stdscr, 300, 20};

    std::vector<int> dinoAnimation;
    for (int i{}; i < 17; ++i)
    {
        dinoAnimation.push_back(1 - i);
    }
    for (int i{16}; i > 0; --i)
    {
        dinoAnimation.push_back(1 - i);
    }

    constexpr int cactusStep{-1};

    int frameCounter{};
    int ch{};

    bool panic{};

    while (true)
    {

        if (panic)
        {
            nodelay(stdscr, false);
            printGameOver();
            getch();
            break;
        }

        ch = getch();

        printScore(score);

        dino.clearPrevious();
        cactus.clearPrevious();

        cactus.move(cactus.x() - 1, cactus.y());
        cactus.print();

        if (cactus.x() < -10)
        {
            cactus.clearPrevious();
            cactus.move(300, cactus.y());
            cactus.nextFrame();
        }




        if (ch != ERR)
            dino.applyAnimation(NcursesModel::Coord::y, dinoAnimation);


        if ((frameCounter % 15) == 0)
        {
            dino.nextFrame();
            frameCounter = 0;
            score += 5;
        }
        dino.print(&panic, true);



        ++frameCounter;
        sleep(16 - (score / 200));

    }




    endwin();

    return 0;
}
