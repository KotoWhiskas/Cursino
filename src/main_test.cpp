#include <curses.h>
#include <ncurses.h>
#include <string>
#include <cassert>

#include "util.h"
#include "event_loop.h"
#include "dino.h"
#include "cactus.h"

int main(int argc, const char* argv[])
{
    double moveRange{40};
    int moveSpeed{16};


    if (argc > 1)
    {
        moveSpeed = std::stoi(argv[1]);

    }

    EventLoop eventLoop{};
    eventLoop.addModel(Dino{}, "dino", 20, 18);

    eventLoop.onKeyPressed("dino", KEY_UP, [&]() {
            eventLoop.vectorAnimate("dino", EventLoop::Direction::y, EventLoop::DirectionValue::negative, 16, 30, true);

    } );

    double cactusSpeedIncrease{};
    int cactusSpawnTimeReduct{};

    static std::size_t index{};
    static std::string id{"cactus"};

    eventLoop.everyMilliseconds(id, 5 * 1000,
        [&]()
        {

            index = eventLoop.modelCount();
            id = "cactus" + std::to_string(index);

            eventLoop.addModel(Cactus{}, id, getmaxx(stdscr) + 10, 17);
            eventLoop.getModel(id).setCurrentFrameNum(getRandom(0, 3));

            eventLoop.onModelMovedTo(id, -10, eventLoop.getModel(id).y(), [&](){ eventLoop.removeModel(id); });
            eventLoop.destAnimate(id, -10, eventLoop.getModel(id).y(), 4. - cactusSpeedIncrease);
            eventLoop.show(id);

            cactusSpeedIncrease += 0.2;
            cactusSpawnTimeReduct += 100;



        }, &cactusSpawnTimeReduct
    );

    eventLoop.everyMilliseconds("dino", 200, [&]()
    {
        eventLoop.getModel("dino").nextFrame();
    }
    );


    eventLoop.show("dino");

    eventLoop.start();

    return 0;
}
