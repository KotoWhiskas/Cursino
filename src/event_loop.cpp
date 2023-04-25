#include "event_loop.h"

#include "util.h"
#include "ncurses_model.h"

#include <chrono>
#include <curses.h>
#include <exception>
#include <ncurses.h>
#include <iostream>
#include <stdexcept>
#include <string>

std::chrono::time_point<std::chrono::steady_clock, std::chrono::milliseconds> getCurrentSteadyMS()
{
    auto time{std::chrono::steady_clock::now()};
    auto timeMS{std::chrono::time_point_cast<std::chrono::milliseconds>(time)};

    return timeMS;
}


EventLoop::EventLoop()
{

}

void EventLoop::start()
{
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);



    while (true)
    {

        auto startMS{getCurrentSteadyMS()};

        executeMoveEvents();
        executeTimeEvents();
        executeKeyEvents();
        executeVectorAnimtaions();
        executeDestinationAnimations();
        executeDrawEvents();

        ++frameCount;
        auto endMS{getCurrentSteadyMS()};

        auto elapsedMS{endMS - startMS};

        static constexpr float fps60sleep{16.66};
        sleep(fps60sleep - elapsedMS.count());
    }

    endwin();
}



void EventLoop::everyMilliseconds(const std::string& associatedWith, int ms, std::function<void()> exec, int* add)
{
    m_timeEvents[associatedWith] = {std::chrono::milliseconds(ms), getCurrentSteadyMS(), exec, add};
}

void EventLoop::executeKeyEvents()
{
    m_lastKeyPress = getch();

    for (auto [id, value] : m_keyPressEvents)
    {
        if (m_lastKeyPress == value.key)
        {
            value.func();
        }
    }

    for (auto [id, value] : m_keyReleaseEvents)
    {
        if (m_lastKeyPress == value.key)
        {
            value.func();
        }
    }
}

void EventLoop::executeTimeEvents()
{
    for (auto& [id, value] : m_timeEvents)
        {
            int add{0};

            if (value.add)
            {
                add = *value.add;
            }

            if ((getCurrentSteadyMS() - value.timePoint) > (value.set - std::chrono::milliseconds(add)))
            {
                value.func();
                value.timePoint = getCurrentSteadyMS();
            }

        }
}

void EventLoop::executeDrawEvents()
{
    clear();
    bool touch{false};

    mvwprintw(stdscr, 0, 0, std::to_string(frameCount / 10).c_str());

    for (auto& [id, modelWrapper] : m_models)
        {
            if (modelWrapper.show)
            {
                touch = drawModel(modelWrapper);
                if (touch && modelWrapper.id == "dino")
                {
                    drawGameOver();
                    nodelay(stdscr, false);
                    getch();
                    std::runtime_error("game over lol");
                }
            }
        }
    refresh();
}

void EventLoop::executeDestinationAnimations()
{

    for (auto& [id, animation] : m_destAnimations)
    {
        auto& model{getModel(id)};

        if (animation.totalX < animation.distanceX)
        {
            animation.totalX += animation.speedX / 60.;
            animation.overcomeX += animation.speedX / 60.;
        }

        if (animation.totalY < animation.distanceY)
        {
           animation.totalY += animation.speedY / 60.;
           animation.overcomeY += animation.speedY / 60.;
        }


        if (animation.overcomeX >= 1)
        {
            model.move(model.x() + animation.stepX, model.y());
            animation.overcomeX -= 1;
        }

        if (animation.overcomeY >= 1)
        {
            model.move(model.x(), model.y() + animation.stepY);
            animation.overcomeY -= 1;
        }

    }
}

// returns true if touches another model
bool EventLoop::drawModel(const ModelWrapper& wrapper) const
{
    const NcursesModel::matrix_t& matrix{wrapper.model.getCurrentMatrix()};

    int rowcenterItem{static_cast<int>(matrix.at(0).size()  / 2)};
    int colcenterItem{static_cast<int>(matrix.size()        / 2)};

    bool touch{false};
    for (int column{}; column < matrix.size(); ++column)
    {
        for (int row{}; row < matrix.at(0).size(); ++row)
        {
                if (matrix[column][row] != ' ' &&
                    mvwinch(stdscr,
                            wrapper.model.y() + column - colcenterItem,
                            wrapper.model.x() + row    - rowcenterItem) != ' ')
                {
                    touch = true;
                }


            mvwaddch(stdscr,
                     wrapper.model.y() + column - colcenterItem,
                     wrapper.model.x() + row    - rowcenterItem,
                     matrix[column][row]);

        }
    }

    return touch;

}

void EventLoop::executeMoveEvents()
{
    for (auto& [id, value] : m_moveEvents)
    {
        NcursesModel& model{getModel("id")};
        if (model.x() == value.x && model.y() == value.y)
            value.func();

    }
}

void EventLoop::executeVectorAnimtaions()
{
    std::vector<std::string> idsToRemove;

    for (auto& [id, animation] : m_animations)
    {

        if (animation.directionValue == DirectionValue::positive )
        {
            animation.step = 1;
        }
        else
        {
            animation.step = -1;
        }


        if (animation.total >= static_cast<double>(animation.distance))
        {
            if (!animation.onRepeat)
            {
                if (animation.loop)
                {
                    animation.onRepeat = true;
                    animation.overcome = 0;
                    animation.total = 0;
                }
            }
            else
            {
                animation.done = true;
                idsToRemove.push_back(id);
            }
        }


        else if (!animation.done)
        {
            animation.overcome += animation.speed / 60.;
            animation.total += animation.speed / 60.;

            if (animation.onRepeat)
            {
                animation.step *= -1;
            }

            if (animation.overcome >= 1)
            {
                auto& model = getModel(animation.id);

                if (animation.direction == Direction::x)
                    model.move(model.x() + animation.step, model.y());

                else if (animation.direction == Direction::y)
                    model.move(model.x(), model.y() + animation.step);

                animation.overcome -= 1;
            }
        }
    }

    for (const std::string& id : idsToRemove)
    {
        m_animations.erase(id);
    }
}
